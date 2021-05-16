/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 23:53:48 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 22:07:19 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_initialize_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		ft_error("Error initializing minilibx", vars);
}

static void	ft_set_resolution(t_vars *vars)
{
	int	win_width;
	int	win_height;

	mlx_get_screen_size(vars->mlx, &win_width, &win_height);
	if (vars->game.resolution.width > win_width)
		vars->game.resolution.width = win_width;
	if (vars->game.resolution.height > win_height)
		vars->game.resolution.height = win_height;
}

static void	ft_initialize_mlx_image(t_vars *vars)
{
	vars->image.image = mlx_new_image(vars->mlx,
			vars->game.resolution.width,
			vars->game.resolution.height);
	if (!vars->image.image)
		ft_error("Error creating game image", vars);
	vars->image.address = mlx_get_data_addr(vars->image.image,
			&vars->image.bits_per_pixel,
			&vars->image.line_length,
			&vars->image.endian);
}

static void	ft_initialize_player(t_player *player)
{
	player->width = 1;
	player->height = 1;
	player->x = ((player->x * TILE) + TILE / 2);
	player->y = ((player->y * TILE) + TILE / 2);
	ft_clean_direction_moviments(player);
}

void	ft_setup(t_vars *vars)
{
	ft_initialize_mlx(vars);
	ft_set_resolution(vars);
	ft_initialize_mlx_image(vars);
	ft_create_texture_images(vars);
	ft_initialize_player(&vars->player);
	ft_initialize_sprites_position(vars->game.sprites.list);
	vars->proj_plane_distance = (vars->game.resolution.width / 2)
		/ tan(FOV_ANGLE / 2);
	vars->minimap = 0;
	vars->window = NULL;
	vars->ray = NULL;
}
