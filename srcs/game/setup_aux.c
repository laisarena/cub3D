/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 17:51:07 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 22:07:45 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_clear_image(t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while (++y < vars->game.resolution.height)
	{
		x = -1;
		while (++x < vars->game.resolution.width)
			ft_put_pixel(&vars->image, x, y, 0x00000000);
	}
}

void	ft_save_bmp_file(t_vars *vars)
{
	if (!vars->bmp_save)
		return ;
	ft_write_bmp_file(vars);
	ft_close(vars);
}

void	ft_create_window(t_vars *vars)
{
	if (vars->window)
		return ;
	vars->window = mlx_new_window(vars->mlx,
			vars->game.resolution.width,
			vars->game.resolution.height,
			"cub3D");
	if (!vars->window)
	{
		ft_free_resources(vars);
		ft_error("Error creating window", vars);
	}
}

void	ft_initialize_sprites_position(t_list *sprite_list)
{
	t_sprite	*sprite;

	while (sprite_list)
	{
		sprite = sprite_list->content;
		sprite->position.x = ((sprite->position.x * TILE) + TILE / 2);
		sprite->position.y = ((sprite->position.y * TILE) + TILE / 2);
		sprite_list = sprite_list->next;
	}
}
