/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:59:04 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 17:29:05 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_calc_wall_height(t_ray ray, float player_angle, int win_width)
{
	float	perp_distance;
	float	distance;

	perp_distance = ray.distance * cos(ray.angle - player_angle);
	distance = (win_width / 2) / tan(FOV_ANGLE / 2);
	return ((int)((TILE / perp_distance) * distance));
}

static t_texture	*ft_get_wall_texture(t_ray ray, t_vars *vars)
{
	if (ray.is_hit_vertical)
	{
		if (ray.angle > 1.5 * PI || ray.angle < 0.5 * PI)
			return (&vars->game.east);
		return (&vars->game.west);
	}
	if (ray.angle > 0 && ray.angle < PI)
		return (&vars->game.south);
	return (&vars->game.north);
}

static int	ft_change_color_intensity(int color, float factor)
{
	int	a;
	int	r;
	int	g;
	int	b;

	a = color & 0xFF000000;
	r = (color & 0x00FF0000) * factor;
	g = (color & 0x0000FF00) * factor;
	b = (color & 0x000000FF) * factor;
	return (a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF));
}

static void	ft_render_wall(t_wall wall, t_ray ray, t_vars *vars, int x)
{
	int				y;
	int				color;

	y = wall.top;
	while (y < wall.bottom)
	{
		wall.texture_offset.y = ft_calc_y_texture_offset(wall, y,
				vars->game.resolution.height, wall.texture);
		color = ft_get_color(&wall.texture->image, wall.texture_offset.x,
				wall.texture_offset.y);
		if (ray.is_hit_vertical)
			color = ft_change_color_intensity(color, 0.7);
		ft_put_pixel(&vars->image, x, y, color);
		y++;
	}
}

void	ft_render_projection(t_vars *vars)
{
	int			x;
	t_wall		wall;

	x = 0;
	while (x < vars->game.resolution.width)
	{
		wall.height = ft_calc_wall_height(vars->ray[x],
				vars->player.rotation_angle,
				vars->game.resolution.width);
		wall.top = ft_calc_top(vars->game.resolution.height, wall.height);
		wall.bottom = ft_calc_bottom(vars->game.resolution.height, wall.height);
		wall.texture = ft_get_wall_texture(vars->ray[x], vars);
		wall.texture_offset.x = ft_calc_x_texture_offset(
				vars->ray[x],
				wall.texture);
		ft_render_ceiling(wall, vars, x);
		ft_render_wall(wall, vars->ray[x], vars, x);
		ft_render_floor(wall, vars, x);
		x++;
	}
}
