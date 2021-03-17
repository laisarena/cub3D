/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 20:51:00 by lfrasson          #+#    #+#             */
/*   Updated: 2021/03/15 21:13:22 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define KEYPRESS	2
#define PI		3.14159265
#define TWO_PI		6.28318530
#define TILE_SIZE	64
#define MAP_ROW		13
#define MAP_COL		20
#define SIZE		500
#define FOV_ANGLE	(60 * (PI / 180))
#define W		119
#define A		97
#define S		115
#define D		100

void	ft_hooks(t_vars *vars);
void	ft_render(t_vars *vars);

int		ft_initialize_window(void **mlx, void **window, t_image_data *image)
{
	if (!(*mlx = mlx_init()))
		ft_error("Error initializing minilibx");
	if (!(*window = mlx_new_window(*mlx, SIZE, SIZE, "cub3D")))
		ft_error("Error creating window");
	if (!(image->image = mlx_new_image(*mlx, SIZE, SIZE)))
		ft_error("Error creating image");
	image->address = mlx_get_data_addr(image->image,
										&image->bits_per_pixel,
										&image->line_length,
										&image->endian);
	return (1);
}

void	ft_put_pixel(t_image_data *image, int x, int y, int color)
{
	int		offset;
	int		bytes_per_pixel;
	char	*address;

	bytes_per_pixel = image->bits_per_pixel / 8;
	offset = y * image->line_length + x * bytes_per_pixel;
	address = image->address + offset;
	*(unsigned int*)address = color;
}

void	rectangle_on_image(t_vars *vars, int width, int heigth, int color)
{
	int i;
	int j;

	i = -1;
	while (++i < heigth)
	{
		j = -1;
		while (++j < width)
			ft_put_pixel(&vars->image, vars->x + j, vars->y + i, color);
	}
}

int		ft_close(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->image.image);
	mlx_destroy_window(vars->mlx, vars->window);
	free(vars->mlx);
	exit(0);
}

void	ft_update(t_vars *vars)
{
	vars->x += 1;
	vars->y += 1;
}

int		ft_y(t_vars *vars)
{
	ft_render(vars);
	ft_update(vars);
	return (0);
}

int		ft_key_press(int keycode, t_vars *vars)
{
	if (keycode == 0xFF1B)
		ft_close(vars);
	if (keycode == W)
		vars->y -= 1;
	if (keycode == A)
		vars->x -= 1;
	if (keycode == S)
		vars->y += 1;
	if (keycode == D)
		vars->x += 1;
	ft_render(vars);
	return (1);
}

void	clear_image(t_vars *vars)
{
	int x;
	int y;

	y = -1;
	while (++y < SIZE)
	{
		x = -1;
		while (++x < SIZE)
			ft_put_pixel(&vars->image, x, y, 0x00000000);
	}
}

void	ft_render(t_vars *vars)
{
	clear_image(vars);
	rectangle_on_image(vars, 30, 50, 0x00FF0000);
	mlx_put_image_to_window(vars->mlx, vars->window, vars->image.image, 0, 0);
}

void	ft_setup(t_vars *vars)
{
	if (!(ft_initialize_window(&vars->mlx, &vars->window, &vars->image)))
		ft_close(vars);
	vars->x = 50;
	vars->y = 50;
}

void	ft_minilibx(t_scene_description *scene_description)
{
	t_vars		vars;

	(void)scene_description;
	ft_setup(&vars);
	ft_render(&vars);
	mlx_hook(vars.window, KEYPRESS, 1L << 0, ft_key_press, &vars);
	mlx_hook(vars.window, 33, 0, ft_close, &vars);
	mlx_loop(vars.mlx);
}
