/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 03:03:15 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 22:08:24 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_initialize_file_image(t_vars *vars, t_texture *texture)
{
	texture->image.image = mlx_xpm_file_to_image(vars->mlx,
			texture->path,
			&texture->width,
			&texture->height);
	if (!texture->image.image)
		ft_error("Error creating texture image", vars);
	texture->image.address = mlx_get_data_addr(texture->image.image,
			&texture->image.bits_per_pixel,
			&texture->image.line_length,
			&texture->image.endian);
}

void	ft_create_texture_images(t_vars *vars)
{
	ft_initialize_file_image(vars, &vars->game.north);
	ft_initialize_file_image(vars, &vars->game.south);
	ft_initialize_file_image(vars, &vars->game.west);
	ft_initialize_file_image(vars, &vars->game.east);
	ft_initialize_file_image(vars, &vars->game.sprites.texture);
}

int	ft_calc_x_texture_offset(t_ray ray, t_texture *texture)
{
	if (ray.is_hit_vertical)
		return ((int)ray.wall_hit.y % texture->width);
	return ((int)ray.wall_hit.x % texture->width);
}

int	ft_calc_y_texture_offset(t_wall wall, int y, int win_height)
{
	int		distance_from_top;
	float	stretch_factor;

	distance_from_top = y + (wall.height / 2) - (win_height / 2);
	stretch_factor = (float)wall.texture->height / wall.height;
	return (distance_from_top * stretch_factor);
}
