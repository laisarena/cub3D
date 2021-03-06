/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 20:51:00 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 19:12:45 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_update(t_vars *vars)
{
	ft_clear_image(vars);
	ft_move_player(vars);
	ft_define_visible_sprites(vars);
	ft_cast_rays(vars);
}

void	ft_render_minimap(t_vars *vars)
{
	if (vars->minimap)
	{
		ft_render_minimap_grid(vars);
		ft_render_minimap_player(vars);
		ft_render_minimap_rays(vars);
		ft_render_minimap_sprites(vars);
	}
}

void	ft_render(t_vars *vars)
{
	ft_render_projection(vars);
	ft_render_sprites_projection(vars);
	ft_render_minimap(vars);
	ft_save_bmp_file(vars);
	ft_create_window(vars);
	mlx_put_image_to_window(vars->mlx, vars->window, vars->image.image, 0, 0);
}

int	ft_loop(t_vars *vars)
{
	ft_update(vars);
	ft_render(vars);
	return (0);
}

void	ft_game(t_vars *vars)
{
	ft_setup(vars);
	ft_loop(vars);
	mlx_hook(vars->window, KEYPRESS, 1L << 0, ft_key_press, vars);
	mlx_hook(vars->window, 33, 0, ft_close, vars);
	mlx_loop_hook(vars->mlx, ft_loop, vars);
	mlx_loop(vars->mlx);
}
