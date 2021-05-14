/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 00:01:31 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/15 00:13:40 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_intersection	ft_init_horiz(t_ray *ray, t_vars *vars)
{
	t_intersection	horiz;

	horiz.intercept.y = floor(vars->player.y / TILE) * TILE;
	if (ray->is_facing_up)
		horiz.intercept.y += TILE;
	horiz.intercept.x = vars->player.x
		+ (horiz.intercept.y - vars->player.y) / tan(ray->angle);
	horiz.step.y = TILE;
	if (ray->is_facing_down)
		horiz.step.y *= -1;
	horiz.step.x = TILE / tan(ray->angle);
	if (ray->is_facing_down)
		horiz.step.x *= -1;
	horiz.next_touch.x = horiz.intercept.x;
	horiz.next_touch.y = horiz.intercept.y;
	horiz.found_wall_hit = 0;
	horiz.wall_hit.x = 0;
	horiz.wall_hit.y = 0;
	horiz.hit_distance = 0;
	return (horiz);
}

t_intersection	ft_init_verti(t_ray *ray, t_vars *vars)
{
	t_intersection	verti;

	verti.intercept.x = floor(vars->player.x / TILE) * TILE;
	if (ray->is_facing_right)
		verti.intercept.x += TILE;
	verti.intercept.y = vars->player.y
		+ (verti.intercept.x - vars->player.x) * tan(ray->angle);
	verti.step.x = TILE;
	if (ray->is_facing_left)
		verti.step.x *= -1;
	verti.step.y = TILE * tan(ray->angle);
	if (ray->is_facing_left)
		verti.step.y *= -1;
	verti.next_touch.x = verti.intercept.x;
	verti.next_touch.y = verti.intercept.y;
	verti.found_wall_hit = 0;
	verti.wall_hit.x = 0;
	verti.wall_hit.y = 0;
	verti.hit_distance = 0;
	return (verti);
}

void	ft_find_intersection_horiz(t_intersection *horiz,
		t_ray *ray, t_vars *vars)
{
	t_coord	check;

	while (1)
	{
		check.x = horiz->next_touch.x;
		check.y = horiz->next_touch.y;
		if (ray->is_facing_up)
			check.y += 1;
		if (ray->is_facing_down)
			check.y -= 1;
		if (ft_is_wall_at(check.x, check.y, vars)
			|| (horiz->next_touch.x <= 0
				&& horiz->next_touch.x >= vars->map.cols * TILE
				&& horiz->next_touch.y <= 0
				&& horiz->next_touch.y >= vars->map.rows *TILE))
		{
			horiz->wall_hit.x = horiz->next_touch.x;
			horiz->wall_hit.y = horiz->next_touch.y;
			horiz->found_wall_hit = 1;
			break ;
		}
		horiz->next_touch.x += horiz->step.x;
		horiz->next_touch.y += horiz->step.y;
	}
}

void	ft_find_intersection_verti(t_intersection *verti,
		t_ray *ray, t_vars *vars)
{
	t_coord	check;

	while (1)
	{
		check.x = verti->next_touch.x;
		check.y = verti->next_touch.y;
		if (ray->is_facing_right)
			check.x += 1;
		if (ray->is_facing_left)
			check.x -= 1;
		if (ft_is_wall_at(check.x, check.y, vars)
			|| (verti->next_touch.x <= 0
				&& verti->next_touch.x >= vars->map.cols * TILE
				&& verti->next_touch.y <= 0
				&& verti->next_touch.y >= vars->map.rows * TILE))
		{
			verti->wall_hit.x = verti->next_touch.x;
			verti->wall_hit.y = verti->next_touch.y;
			verti->found_wall_hit = 1;
			break ;
		}
		verti->next_touch.x += verti->step.x;
		verti->next_touch.y += verti->step.y;
	}
}
