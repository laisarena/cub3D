/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:24:15 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/24 23:10:20 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_distance_between_points(float x1, float y1, float x2, float y2)
{
	float	x_sq;
	float	y_sq;

	x_sq = (x2 - x1) * (x2 - x1);
	y_sq = (y2 - y1) * (y2 - y1);
	return (sqrt( x_sq + y_sq ));
}

float	ft_normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

static void	ft_where_ray_facing(t_ray *ray)
{
	ray->is_facing_up = ray->angle > 0 && ray->angle < PI;
	ray->is_facing_down = !ray->is_facing_up;
	ray->is_facing_right = ray->angle < 0.5 * PI && ray->angle > 3.5 * PI;
	ray->is_facing_left = !ray->is_facing_right;
}

static t_intersection	ft_init_horiz(t_ray *ray, t_vars *vars)
{
	t_intersection	horiz;
	
	horiz.intercept.y = floor(vars->player.y / TILE) * TILE;
	if (ray->is_facing_down)
		horiz.intercept.y += TILE;
	horiz.intercept.x = vars->player.x +
		(horiz.intercept.y - vars->player.y) / tan(ray->angle);	
	horiz.step.y = TILE;
	if (ray->is_facing_up)
		horiz.step.y *= -1;
	horiz.step.x = TILE / tan(ray->angle);
	if (ray->is_facing_left && horiz.step.x > 0)
		horiz.step.x *= -1;
	if (ray->is_facing_right && horiz.step.x < 0)
		horiz.step.x *= -1;
	horiz.next_touch.x = horiz.intercept.x;
	horiz.next_touch.y = horiz.intercept.y;
	horiz.found_wall_hit = 0;
	horiz.wall_hit.x = 0;
	horiz.wall_hit.y = 0;
	horiz.wall_content = 0;
	return (horiz);
}

static t_intersection	ft_init_verti(t_ray *ray, t_vars *vars)
{
	t_intersection	verti;
	
	verti.intercept.x = floor(vars->player.y / TILE) * TILE;
	if (ray->is_facing_right)
		verti.intercept.x += TILE;
	verti.intercept.y = vars->player.y +
		(verti.intercept.x - vars->player.x) * tan(ray->angle);	
	verti.step.x = TILE;
	if (ray->is_facing_left)
		verti.step.x *= -1;
	verti.step.y = TILE * tan(ray->angle);
	if (ray->is_facing_up && verti.step.y > 0)
		verti.step.y *= -1;
	if (ray->is_facing_down && verti.step.y < 0)
		verti.step.y *= -1;
	verti.next_touch.x = verti.intercept.x;
	verti.next_touch.y = verti.intercept.y;
	verti.found_wall_hit = 0;
	verti.wall_hit.x = 0;
	verti.wall_hit.y = 0;
	verti.wall_content = 0;
	return (verti);
}

static void	ft_find_intersection_horiz(t_intersection *horiz, t_ray *ray, t_vars *vars)
{
	t_coordinate	check;

	while (horiz->next_touch.x >= 0
			&& horiz->next_touch.x <= vars->scene_description.resolution.x
			&& horiz->next_touch.y >= 0
			&& horiz->next_touch.y <= vars->scene_description.resolution.y)
	{
		check.x = horiz->next_touch.x;
		check.y = horiz->next_touch.y; 
		if (ray->is_facing_up)
			check.y += 1;
		if (ft_is_wall_at(check.x, check.y, vars))
		{
			horiz->wall_hit.x = horiz->next_touch.x;
			horiz->wall_hit.y = horiz->next_touch.y;
			horiz->wall_content = vars->map.matrix[(int)floor(check.y / TILE)]
				[(int)floor(check.x / TILE)];
			horiz->found_wall_hit = 1;
			break ;
		}
		horiz->next_touch.x += horiz->step.x;
		horiz->next_touch.y += horiz->step.y;
	}
}

static void	ft_find_intersection_verti(t_intersection *verti, t_ray *ray, t_vars *vars)
{
	t_coordinate	check;

	while (verti->next_touch.x >= 0
			&& verti->next_touch.x <= vars->scene_description.resolution.x
			&& verti->next_touch.y >= 0
			&& verti->next_touch.y <= vars->scene_description.resolution.y)
	{
		check.x = verti->next_touch.x;
		check.y = verti->next_touch.y; 
		if (ray->is_facing_left)
			check.x += 1;
		if (ft_is_wall_at(check.x, check.y, vars))
		{
			verti->wall_hit.x = verti->next_touch.x;
			verti->wall_hit.y = verti->next_touch.y;
			//verti->wall_content = vars->map.matrix[(int)floor(check.y / TILE)]
			//	[(int)floor(check.x / TILE)];
			verti->found_wall_hit = 1;
			break ;
		}
		verti->next_touch.x += verti->step.x;
		verti->next_touch.y += verti->step.y;
	}
}
static void	ft_distance(t_intersection *inter,t_vars *vars)
{
	inter->hit_distance = INT_MAX;
	if (inter->found_wall_hit)
	inter->hit_distance = ft_distance_between_points(
			vars->player.x, vars->player.y,
			inter->wall_hit.x, inter->wall_hit.y);
}

static void	ft_set_hit_wall(t_intersection *inter, t_ray *ray)
{
	ray->distance =inter->hit_distance;
	ray->wall_hit.x =inter->wall_hit.x;
	ray->wall_hit.y =inter->wall_hit.y;
	ray->wall_hit_content =inter->wall_content;
}

static void	ft_cast_single_ray(t_ray *ray, t_vars *vars)
{
	t_intersection	horiz;
	t_intersection	verti;
	
	ft_where_ray_facing(ray);
	horiz = ft_init_horiz(ray, vars); 
	verti = ft_init_verti(ray, vars); 
	ft_find_intersection_horiz(&horiz, ray, vars);
	ft_find_intersection_verti(&verti, ray, vars);

	ft_distance(&horiz, vars);
	ft_distance(&verti, vars);

	if (verti.hit_distance < horiz.hit_distance)
	{
		ft_set_hit_wall(&verti, ray);
		ray->is_hit_vertical = 1;
	}
	else
	{
		ft_set_hit_wall(&horiz, ray);
		ray->is_hit_vertical = 0;
	}

}

void	ft_cast_rays(t_vars *vars)
{
	float	ray_angle;
	int		strip;
	int		num_rays;

	num_rays = TILE * vars->map.cols;
	//num_rays = vars->scene_description.resolution.x;
	ray_angle = vars->player.rotation_angle - (FOV_ANGLE / 2);
	vars->ray = malloc(sizeof(t_ray) * (num_rays + 1)); 
	strip = 0;
	while (strip < num_rays)
	{
		vars->ray[strip].angle = ft_normalize_angle(ray_angle);
		ft_cast_single_ray(&vars->ray[strip], vars);
		ray_angle += FOV_ANGLE / num_rays;
		strip++;
	}
}