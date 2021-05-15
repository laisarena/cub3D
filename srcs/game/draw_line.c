/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 23:01:39 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/15 19:57:29 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_line(t_vars *vars,
					t_int_coord p0,
					t_int_coord p1,
					int color)
{
	t_coord	position;
	t_coord	delta;
	float	step;
	int		i;

	delta.x = (float)(p1.x - p0.x);
	delta.y = (float)(p1.y - p0.y);
	if (fabs(delta.x) > fabs(delta.y))
		step = fabs(delta.x);
	else
		step = fabs(delta.y);
	delta.x = delta.x / step;
	delta.y = delta.y / step;
	position.x = p0.x;
	position.y = p0.y;
	i = 0;
	while (i++ < step)
	{
		ft_put_pixel(&vars->image, position.x, position.y, color);
		position.x += delta.x;
		position.y += delta.y;
	}
}
