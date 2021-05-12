/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 23:53:48 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/12 19:09:33 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_initialize_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		ft_error("Error initializing minilibx");
}

static void	ft_initialize_mlx_image(t_vars *vars)
{
	vars->image.image = mlx_new_image(vars->mlx,
			vars->game.resolution.width,
			vars->game.resolution.height);
	if (!vars->image.image)
		ft_error("Error creating game image");
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

static void	ft_initialize_sprites_position(t_list *sprites_position)
{
	t_coord	*position;

	while (sprites_position)
	{
		position = sprites_position->content;
		position->x = ((position->x * TILE) + TILE / 2);
		position->y = ((position->y * TILE) + TILE / 2);
		sprites_position = sprites_position->next;
	}
}

void	ft_setup(t_vars *vars)
{
	ft_initialize_mlx(vars);
	ft_initialize_mlx_image(vars);
	ft_create_texture_images(vars);
	ft_initialize_player_position(vars);
	ft_initialize_sprites_position(vars->game.sprites.position);
	ft_reset_moviments(&vars->player);
}
