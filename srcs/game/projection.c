/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 02:57:27 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/08 00:49:53 by lfrasson         ###   ########.fr       */
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

static int	ft_calc_wall_top(int win_hight, int wall_height)
{
	int	top;

	top = (win_hight / 2) - (wall_height / 2);
	if (top < 0)
		return (0);
	return (top);
}

static int	ft_calc_wall_bottom(int win_height, int wall_height)
{
	int	bottom;

	bottom = (win_height / 2) + (wall_height / 2);
	if (bottom > win_height)
		return (win_height);
	return (bottom);
}

static void	ft_render_ceiling(t_wall wall, t_vars *vars, int x)
{
	int	y;

	y = 0;
	while (y < wall.top)
		ft_put_pixel(&vars->image,
			x,
			y++,
			vars->scene_description.ceilling.hex);
}

static void	ft_render_floor(t_wall wall, t_vars *vars, int x)
{
	int	y;

	y = wall.bottom;
	while (y < vars->scene_description.resolution.y)
		ft_put_pixel(&vars->image,
			x,
			y++,
			vars->scene_description.floor.hex);
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

static t_image_data	*ft_get_texture_image(t_ray ray, t_vars *vars)
{
	if (ray.is_hit_vertical)
	{
		if (ray.angle > 1.5 * PI || ray.angle < 0.5 * PI)
			return (&vars->scene_description.east.image);
		return (&vars->scene_description.west.image);
	}
	if (ray.angle > 0 && ray.angle < PI)
		return (&vars->scene_description.south.image);
	return (&vars->scene_description.north.image);
}

static void	ft_render_wall(t_wall wall, t_ray ray, t_vars *vars, int x)
{
	int				y;
	int				color;
	t_image_data	*image;

	y = wall.top;
	while (y < wall.bottom)
	{
		wall.texture_offset.y = ft_calc_y_texture_offset(wall, y,
				vars->scene_description.resolution.y);
		image = ft_get_texture_image(ray, vars);
		color = ft_get_color(image, wall.texture_offset.x,
				wall.texture_offset.y);
		if (ray.is_hit_vertical)
			ft_put_pixel(&vars->image, x, y, color);
		else
			ft_put_pixel(&vars->image, x, y, color);
		y++;
	}
}

void	ft_render_3d_projection(t_vars *vars)
{
	int		x;
	t_wall	wall;

	x = 0;
	while (x < vars->scene_description.resolution.x)
	{
		wall.height = ft_calc_wall_height(vars->ray[x],
				vars->player.rotation_angle,
				vars->scene_description.resolution.x);
		wall.top = ft_calc_wall_top(vars->scene_description.resolution.y,
				wall.height);
		wall.bottom = ft_calc_wall_bottom(vars->scene_description.resolution.y,
				wall.height);
		wall.texture_offset.x = ft_calc_x_texture_offset(vars->ray[x]);
		ft_render_ceiling(wall, vars, x);
		ft_render_wall(wall, vars->ray[x], vars, x);
		ft_render_floor(wall, vars, x);
		x++;
	}
}
