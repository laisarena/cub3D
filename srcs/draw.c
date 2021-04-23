/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 03:21:08 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/20 01:30:11 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_pixel(t_image_data *image, int x, int y, int color)
{
	int		offset;
	int		bytes_per_pixel;
	char	*address;

	bytes_per_pixel = image->bits_per_pixel / 8;
	offset = y * image->line_length + x * bytes_per_pixel;
	address = image->address + offset;
	*(unsigned int *)address = color;
}

void	ft_rectangle_on_image(t_vars *vars, int width, int heigth,
							int color, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < heigth)
	{
		j = -1;
		while (++j < width)
			ft_put_pixel(&vars->image, x + j, y + i, color);
	}
}
