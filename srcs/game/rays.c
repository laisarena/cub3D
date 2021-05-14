/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:24:15 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/15 00:18:11 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_intersection	ft_init_horiz(t_ray *ray, t_vars *vars);
t_intersection	ft_init_verti(t_ray *ray, t_vars *vars);
void			ft_find_intersection_horiz(t_intersection *horiz,
					t_ray *ray, t_vars *vars);
void			ft_find_intersection_verti(t_intersection *verti,
					t_ray *ray, t_vars *vars);

static void	ft_where_ray_facing(t_ray *ray)
{
	ray->is_facing_up = ray->angle > 0 && ray->angle < PI;
	ray->is_facing_down = !ray->is_facing_up;
	ray->is_facing_right = ray->angle < (0.5 * PI) || ray->angle > (1.5 * PI);
	ray->is_facing_left = !ray->is_facing_right;
}

static void	ft_distance(t_intersection *inter, t_vars *vars)
{
	inter->hit_distance = INT_MAX;
	if (inter->found_wall_hit)
		inter->hit_distance = ft_distance_between_points(
				vars->player.x, vars->player.y,
				inter->wall_hit.x, inter->wall_hit.y);
}

static void	ft_set_hit_wall(t_intersection *inter, t_ray *ray)
{
	ray->distance = inter->hit_distance;
	ray->wall_hit.x = inter->wall_hit.x;
	ray->wall_hit.y = inter->wall_hit.y;
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
	float	angle;
	int		column;
	int		num_rays;

	num_rays = vars->game.resolution.width;
	vars->ray = malloc(sizeof(t_ray) * (num_rays + 1));
	column = 0;
	while (column < num_rays)
	{
		angle = atan((column - (float)(num_rays / 2))
				/ vars->proj_plane_distance);
		ray_angle = vars->player.rotation_angle + angle;
		vars->ray[column].angle = ft_normalize_angle(ray_angle);
		ft_cast_single_ray(&vars->ray[column], vars);
		ray_angle += FOV_ANGLE / num_rays;
		column++;
	}
}
