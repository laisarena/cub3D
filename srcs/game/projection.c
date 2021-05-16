/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 02:57:27 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 17:06:05 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_get_color(t_image_data *image, int x, int y)
{
	int		offset;
	int		bytes_per_pixel;
	int		color;
	char	*address;

	bytes_per_pixel = image->bits_per_pixel / 8;
	offset = y * image->line_length + x * bytes_per_pixel;
	address = image->address + offset;
	color = *(unsigned int *)address;
	return (color);
}

float	ft_calc_top(int win_hight, int height)
{
	float	top;

	top = (win_hight / 2) - (height / 2);
	if (top < 0)
		return (0);
	return (top);
}

float	ft_calc_bottom(int win_height, int height)
{
	float	bottom;

	bottom = (win_height / 2) + (height / 2);
	if (bottom > win_height)
		return (win_height);
	return (bottom);
}

void	ft_render_ceiling(t_wall wall, t_vars *vars, int x)
{
	int	y;

	if (wall.top > vars->game.resolution.height)
		return ;
	y = 0;
	while (y < wall.top)
		ft_put_pixel(&vars->image,
			x,
			y++,
			vars->game.ceilling.hex);
}

void	ft_render_floor(t_wall wall, t_vars *vars, int x)
{
	int	y;

	if (wall.bottom > vars->game.resolution.height
		|| wall.bottom < 0)
		return ;
	y = wall.bottom;
	while (y < vars->game.resolution.height)
		ft_put_pixel(&vars->image,
			x,
			y++,
			vars->game.floor.hex);
}
