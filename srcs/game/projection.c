/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 02:57:27 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/14 21:59:38 by lfrasson         ###   ########.fr       */
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

float	ft_calc_top(int win_hight, int height)
{
	float	top;

	top = (win_hight / 2) - (height / 2);
	if (top < 0)
		return (0);
	return (top);
}

float	ft_calc_bottom(int win_height, int height)
{
	float	bottom;

	bottom = (win_height / 2) + (height / 2);
	if (bottom > win_height)
		return (win_height);
	return (bottom);
}

static void	ft_render_ceiling(t_wall wall, t_vars *vars, int x)
{
	int	y;

	if (wall.top > vars->game.resolution.height)
		return ;
	y = 0;
	while (y < wall.top)
		ft_put_pixel(&vars->image,
			x,
			y++,
			vars->game.ceilling.hex);
}

static void	ft_render_floor(t_wall wall, t_vars *vars, int x)
{
	int	y;

	if (wall.bottom > vars->game.resolution.height
		|| wall.bottom < 0)
		return ;
	y = wall.bottom;
	while (y < vars->game.resolution.height)
		ft_put_pixel(&vars->image,
			x,
			y++,
			vars->game.floor.hex);
}

int	ft_get_color(t_image_data *image, int x, int y)
{
	int		offset;
	int		bytes_per_pixel;
	int		color;
	char	*address;

	bytes_per_pixel = image->bits_per_pixel / 8;
	offset = y * image->line_length + x * bytes_per_pixel;
	address = image->address + offset;
	color = *(unsigned int *)address;
	return (color);
}

static t_texture	*ft_get_texture(t_ray ray, t_vars *vars)
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

static void	ft_render_wall(t_wall wall, t_ray ray, t_vars *vars, int x, t_texture *texture)
{
	int				y;
	int				color;

	y = wall.top;
	while (y < wall.bottom)
	{
		wall.texture_offset.y = ft_calc_y_texture_offset(wall, y,
				vars->game.resolution.height, texture);
		color = ft_get_color(&texture->image, wall.texture_offset.x,
				wall.texture_offset.y);
		if (ray.is_hit_vertical)
			color = ft_change_color_intensity(color, 0.7);
		ft_put_pixel(&vars->image, x, y, color);
		y++;
	}
}

void	ft_render_3d_projection(t_vars *vars)
{
	int			x;
	t_wall		wall;
	t_texture	*texture;

	x = 0;
	while (x < vars->game.resolution.width)
	{
		wall.height = ft_calc_wall_height(vars->ray[x],
				vars->player.rotation_angle,
				vars->game.resolution.width);
		wall.top = ft_calc_top(vars->game.resolution.height, wall.height);
		wall.bottom = ft_calc_bottom(vars->game.resolution.height, wall.height);
		texture = ft_get_texture(vars->ray[x], vars);
		wall.texture_offset.x = ft_calc_x_texture_offset(vars->ray[x], texture);
		ft_render_ceiling(wall, vars, x);
		ft_render_wall(wall, vars->ray[x], vars, x, texture);
		ft_render_floor(wall, vars, x);
		x++;
	}
}
