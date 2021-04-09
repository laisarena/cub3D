/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 20:51:00 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/09 02:15:18 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define KEYPRESS	2
#define PI			3.14159265
#define TWO_PI		6.28318530
#define MAP_ROW		13
#define MAP_COL		20
#define FOV_ANGLE	(60 * (PI / 180))
#define W			119
#define A			97
#define S			115
#define D			100
#define LEFT		65361
#define RIGTH		65363
#define MINI_FACTOR	1

void	ft_hooks(t_vars *vars);
void	ft_render(t_vars *vars);

int		ft_initialize_window(t_vars *vars)
{
	if (!(vars->mlx = mlx_init()))
		ft_error("Error initializing minilibx");
	if (!(vars->window = mlx_new_window(vars->mlx,
					vars->scene_description.resolution.x,
					vars->scene_description.resolution.y, "cub3D")))
		ft_error("Error creating window");
	if (!(vars->image.image = mlx_new_image(vars->mlx,
					vars->scene_description.resolution.x,
					vars->scene_description.resolution.y)))
		ft_error("Error creating image");
	vars->image.address = mlx_get_data_addr(vars->image.image,
										&vars->image.bits_per_pixel,
										&vars->image.line_length,
										&vars->image.endian);
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

void	rectangle_on_image(t_vars *vars, int width, int heigth, int color, int x, int y)
{
	int i;
	int j;

	i = -1;
	while (++i < heigth)
	{
		j = -1;
		while (++j < width)
			ft_put_pixel(&vars->image, x + j, y + i, color);
	}
}

int		ft_close(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->image.image);
	mlx_destroy_window(vars->mlx, vars->window);
	free(vars->mlx);
	ft_free_map(vars);
	exit(0);
}

void	ft_update(t_vars *vars)
{
	vars->player.x += 1;
	vars->player.y += 1;
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
		vars->player.y -= 1;
	if (keycode == A)
		vars->player.x -= 1;
	if (keycode == S)
		vars->player.y += 1;
	if (keycode == D)
		vars->player.x += 1;
	if (keycode == LEFT)
		vars->player.rotationAngle -= 0.1;
	if (keycode == RIGTH)
		vars->player.rotationAngle += 0.1;
	ft_render(vars);
	return (1);
}

void	clear_image(t_vars *vars)
{
	int x;
	int y;

	y = -1;
	while (++y < vars->scene_description.resolution.y)
	{
		x = -1;
		while (++x < vars->scene_description.resolution.x)
			ft_put_pixel(&vars->image, x, y, 0x00000000);
	}
}

void	ft_renderPlayer(t_vars *vars)
{
	rectangle_on_image(vars,
			vars->player.width * MINI_FACTOR,
			vars->player.height * MINI_FACTOR,
			0x00FF0000,
			vars->player.x * MINI_FACTOR,
			vars->player.y * MINI_FACTOR);

	draw_line(vars,
			vars->player.x * MINI_FACTOR,
			vars->player.y * MINI_FACTOR, 
			(vars->player.x + cos(vars->player.rotationAngle) * 40) * MINI_FACTOR,
			(vars->player.y + sin(vars->player.rotationAngle ) * 40) * MINI_FACTOR,
			0x00FF0000);
}

void	ft_renderMap(t_vars *vars)
{
	int i;
	int j;
	int tile_w;
	int tile_h;
	int color;
	
	tile_w = vars->scene_description.resolution.x /
				vars->scene_description.map.cols;
	tile_h = vars->scene_description.resolution.y /
				vars->scene_description.map.rows;

	tile_w = MINI_FACTOR * tile_w; 
	tile_h = MINI_FACTOR * tile_h; 
	i = 0;
	while (i < vars->scene_description.map.rows)
	{
		j = 0;
		while (j < vars->scene_description.map.cols)
		{
			if (vars->scene_description.map.matrix[i][j] == '1')
				color = 0x00FFFFFF;
			else
				color = 0x00000000;
			rectangle_on_image(vars, tile_w, tile_h, color, j * tile_w, i * tile_h);
			j++;
		}
		i++;
	}
}

void	ft_render(t_vars *vars)
{
	clear_image(vars);
	ft_renderMap(vars);
	//ft_renderRays(vars);
	ft_renderPlayer(vars);
	//rectangle_on_image(vars, 30, 50, 0x00FF0000);
	mlx_put_image_to_window(vars->mlx, vars->window, vars->image.image, 0, 0);
}

void	ft_setup(t_vars *vars)
{
	if (!(ft_initialize_window(vars)))
		ft_close(vars);
	vars->player.width = 1;
	vars->player.height = 1;
	vars->player.x = vars->scene_description.resolution.x / 2;
	vars->player.y = vars->scene_description.resolution.y / 2;
	vars->player.rotationAngle = PI / 2;
}

void	ft_minilibx(t_vars *vars)
{

	ft_setup(vars);
	ft_render(vars);
	mlx_hook(vars->window, KEYPRESS, 1L << 0, ft_key_press, vars);
	mlx_hook(vars->window, 33, 0, ft_close, vars);
	mlx_loop(vars->mlx);
}
