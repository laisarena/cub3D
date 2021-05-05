/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 20:51:00 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/06 01:52:26 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_initialize_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		ft_error("Error initializing minilibx");
}

void	ft_initialize_image(t_vars *vars)
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

int	ft_close(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->image.image);
	if (vars->window)
		mlx_destroy_window(vars->mlx, vars->window);
	free(vars->mlx);
	ft_free_map(vars);
	exit(0);
}

void	ft_clear_image(t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while (++y < vars->scene_description.resolution.y)
	{
		x = -1;
		while (++x < vars->scene_description.resolution.x)
			ft_put_pixel(&vars->image, x, y, 0x00000000);
	}
}
int	ft_write_bmp_file(t_vars *vars);

static void	ft_bmp_file(t_vars *vars)
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
			vars->scene_description.resolution.x,
			vars->scene_description.resolution.y, "cub3D");
	if (!vars->window)
		ft_error("Error creating window");
}

void	ft_render(t_vars *vars)
{
	ft_clear_image(vars);
	ft_move_player(vars);
	ft_reset_moviments(&vars->player);
	ft_cast_rays(vars);
	ft_render_3d_projection(vars);

	ft_render_minimap(vars);
	ft_render_player(vars);
	ft_rende_rays(vars);
	ft_bmp_file(vars);
	ft_create_window(vars);
	mlx_put_image_to_window(vars->mlx, vars->window, vars->image.image, 0, 0);
}

void	ft_initialize_player_position(t_vars *vars)
{
	vars->player.width = 1;
	vars->player.height = 1;
	vars->player.x = vars->scene_description.resolution.x / 2;
	vars->player.y = vars->scene_description.resolution.y / 2;
	vars->player.rotation_angle = 6.22;
}

void	ft_setup(t_vars *vars)
{
	ft_initialize_mlx(vars);
	ft_initialize_image(vars);
	ft_initialize_player_position(vars);
	ft_reset_moviments(&vars->player);
}

void	ft_game(t_vars *vars)
{
	ft_setup(vars);
	ft_render(vars);
	mlx_put_image_to_window(vars->mlx, vars->window, vars->image.image, 0, 0);
	mlx_hook(vars->window, KEYPRESS, 1L << 0, ft_key_press, vars);
	mlx_hook(vars->window, 33, 0, ft_close, vars);
	mlx_loop(vars->mlx);
}
