/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 03:03:15 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/07 22:38:16 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_initialize_file_image(t_vars *vars,
		t_texture *texture)
{
	texture->image.image = mlx_xpm_file_to_image(vars->mlx,
			texture->path,
			&texture->width,
			&texture->height);
	if (!texture->image.image)
		ft_error("Error creating texture image");
	texture->image.address = mlx_get_data_addr(texture->image.image,
			&texture->image.bits_per_pixel,
			&texture->image.line_length,
			&texture->image.endian);
}

void	ft_create_texture_images(t_vars *vars)
{
	ft_initialize_file_image(vars, &vars->scene_description.north);
	ft_initialize_file_image(vars, &vars->scene_description.south);
	ft_initialize_file_image(vars, &vars->scene_description.west);
	ft_initialize_file_image(vars, &vars->scene_description.east);
}

int	ft_calc_x_texture_offset(t_ray ray)
{
	if (ray.is_hit_vertical)
		return ((int)ray.wall_hit.y % TILE);
	return ((int)ray.wall_hit.x % TILE);
}

int	ft_calc_y_texture_offset(t_wall wall, int y, int win_height)
{
	int		distance_from_top;
	float	stretch_factor;

	distance_from_top = y + (wall.height / 2) - (win_height / 2);
	stretch_factor = (float)32 / wall.height;
	return (distance_from_top * stretch_factor);
}
