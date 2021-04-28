/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 02:57:27 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/28 03:47:26 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct
{
	float	perp_distance;
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
		wall.perp_distance = vars->ray[i].distance
			* cos(vars->ray[i].angle - vars->player.rotation_angle);
		wall.distance = (vars->scene_description.resolution.x / 2)
			/ tan(FOV_ANGLE / 2);
		wall.height = (int)((TILE / wall.perp_distance) * wall.distance);
		wall.top = (vars->scene_description.resolution.y / 2) - (wall.height / 2);
		if (wall.top < 0)
			wall.top = 0;
		wall.bottom = (vars->scene_description.resolution.y / 2) + (wall.height / 2);
		if (wall.bottom > vars->scene_description.resolution.y)
		wall.bottom = vars->scene_description.resolution.y;
		y = wall.top;
		while(y < wall.bottom)
		{
			if (vars->ray[i].is_hit_vertical)
				ft_put_pixel(&vars->image, i, y, 0xFFFFFFFF);
			else
				ft_put_pixel(&vars->image, i, y, 0xFFCCCCCC);
			y++;
		}
		i++;
	}

}
