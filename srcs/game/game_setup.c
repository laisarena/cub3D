/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 23:53:48 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/08 03:12:05 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_initialize_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		ft_error("Error initializing minilibx");
}

static void	ft_initialize_image(t_vars *vars)
{
	vars->image.image = mlx_new_image(vars->mlx,
			vars->scene_description.resolution.x,
			vars->scene_description.resolution.y);
	if (!vars->image.image)
		ft_error("Error creating image");
	vars->image.address = mlx_get_data_addr(vars->image.image,
			&vars->image.bits_per_pixel,
			&vars->image.line_length,
			&vars->image.endian);
}

static void	ft_initialize_player_position(t_vars *vars)
{
	vars->player.width = 1;
	vars->player.height = 1;
	vars->player.x = ((vars->player.x * TILE) + TILE / 2);
	vars->player.y = ((vars->player.y * TILE) + TILE / 2);
}

void	ft_setup(t_vars *vars)
{
	ft_initialize_mlx(vars);
	ft_initialize_image(vars);
	ft_create_texture_images(vars);
	ft_initialize_player_position(vars);
	ft_reset_moviments(&vars->player);
}
