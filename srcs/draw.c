/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 03:21:08 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/28 19:19:01 by lfrasson         ###   ########.fr       */
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

void	ft_rectangle_on_image(t_vars *vars, t_retangle retangle, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < retangle.height)
	{
		j = -1;
		while (++j < retangle.width)
			ft_put_pixel(&vars->image,
					retangle.position.x + j,
					retangle.position.y + i,
					color);
	}
}
