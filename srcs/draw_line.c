/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 23:01:39 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/09 00:03:13 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	abs(int value)
{
	if (value < 0)
		return (value * -1);
	return (value);
}

void	draw_line(t_vars *vars, int x0, int y0, int x1, int y1, int color)
{
	float x;
	float y;
	float dx;
	float dy;
	float step;
	int i;

	dx = (float)(x1 - x0);
	dy = (float)(y1 - y0);

	if (abs(dx) > abs(dy))
		step = abs(dx);
	else
		step = abs(dy);

	dx = dx/step;
	dy = dy/step;
	x = x0;
	y = y0;
	i = 0;
	while(i++ < step)
	{
		ft_put_pixel(&vars->image, x, y, color);
		x += dx;
		y += dy;
	}
}
