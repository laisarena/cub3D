/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:24:15 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/23 03:21:24 by lfrasson         ###   ########.fr       */
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
	ray->is_facing_up = ray->angle < 0.5 * PI && ray->angle > 3.5 * PI;
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

static void	ft_cast_single_ray(t_ray *ray, t_vars *vars)
{
	t_intersection	horiz;
	
	ft_where_ray_facing(ray);
	horiz = ft_init_horiz(ray, vars); 
	ft_find_intersection_horiz(&horiz, ray, vars);
}

void	ft_cast_rays(t_vars *vars)
{
	float	ray_angle;
	int		strip;
	int		num_rays;

	num_rays = vars->scene_description.resolution.x;
	ray_angle = vars->player.rotation_angle - (FOV_ANGLE / 2);
	vars->ray = malloc(sizeof(t_ray) * num_rays); 	
	strip = 0;
	while (strip < num_rays)
	{
		vars->ray[strip].angle = ft_normalize_angle(ray_angle);
		ft_cast_single_ray(&vars->ray[strip], vars);
		ray_angle += FOV_ANGLE / num_rays;
		strip++;
	}
}

/*void	ft_rende_rays(t_vars *vars)
{
}*/
