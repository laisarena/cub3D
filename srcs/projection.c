/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 02:57:27 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/28 03:21:57 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct
{
	float	distance;
	int		height;
	int		top;
	int		bottom;
}		t_wall;

void	ft_render_3d_projection(t_vars *vars)
{
	int i;
	int	y;
	t_wall	wall;

	i = 0;
	while(i < vars->scene_description.resolution.x)
	{
		wall.distance = (vars->scene_description.resolution.x / 2)
			/ tan(FOV_ANGLE / 2);
		wall.height = (int)((TILE / vars->ray[i].distance) * wall.distance);
		wall.top = (vars->scene_description.resolution.y / 2) - (wall.height / 2);
		if (wall.top < 0)
			wall.top = 0;
		wall.bottom = (vars->scene_description.resolution.y / 2) + (wall.height / 2);
		if (wall.bottom > vars->scene_description.resolution.y)
		wall.bottom = vars->scene_description.resolution.y;
		y = wall.top;
		while(y < wall.bottom)
		{
			ft_put_pixel(&vars->image, i, y, 0xFFFFFFFF);
			y++;
		}
		i++;
	}

}
