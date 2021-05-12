/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 00:01:38 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/13 00:06:01 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_distance_between_points(float x1, float y1, float x2, float y2)
{
	float	x_sq;
	float	y_sq;

	x_sq = (x2 - x1) * (x2 - x1);
	y_sq = (y2 - y1) * (y2 - y1);
	return (sqrt(x_sq + y_sq));
}

float	ft_normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}
