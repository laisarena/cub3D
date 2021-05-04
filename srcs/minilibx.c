
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 20:51:00 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/05 01:02:07 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_initialize_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		ft_error("Error initializing minilibx");
	vars->window = mlx_new_window(vars->mlx,
			vars->scene_description.resolution.x,
			vars->scene_description.resolution.y, "cub3D");
	if (!vars->window)
		ft_error("Error creating window");
	vars->image.image = mlx_new_image(vars->mlx,
			vars->scene_description.resolution.x,
			vars->scene_description.resolution.y);
	if (!vars->image.image)
		ft_error("Error creating image");
	vars->image.address = mlx_get_data_addr(vars->image.image,
			&vars->image.bits_per_pixel,
			&vars->image.line_length,
			&vars->image.endian);
	return (1);
}

int	ft_close(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->image.image);
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
	mlx_put_image_to_window(vars->mlx, vars->window, vars->image.image, 0, 0);
}

void	ft_setup(t_vars *vars)
{
	if (!(ft_initialize_window(vars)))
		ft_close(vars);
	vars->player.width = 1;
	vars->player.height = 1;
	vars->player.x = vars->scene_description.resolution.x / 2;
	//vars->player.x = 70; 
	vars->player.y = vars->scene_description.resolution.y / 2;
	//vars->player.y = 70;
	vars->player.rotation_angle = 6.22;
	ft_reset_moviments(&vars->player);
}

int	ft_write_bmp_file(t_vars *vars);
void	ft_minilibx(t_vars *vars)
{
	ft_setup(vars);
	ft_render(vars);
	ft_write_bmp_file(vars);
	mlx_hook(vars->window, KEYPRESS, 1L << 0, ft_key_press, vars);
	mlx_hook(vars->window, 33, 0, ft_close, vars);
	mlx_loop(vars->mlx);
}
