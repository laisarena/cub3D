/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 23:22:33 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/29 03:06:24 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_render_minimap_rays(t_vars *vars)
{
	int					i;
	t_int_coord	player;
	t_int_coord	wall;

	player.x = vars->player.x * MINI_FACTOR;
	player.y = vars->player.y * MINI_FACTOR;
	i = 0;
	while (i < vars->game.resolution.x)
	{
		wall.x = vars->ray[i].wall_hit.x * MINI_FACTOR;
		wall.y = vars->ray[i].wall_hit.y * MINI_FACTOR;
		ft_draw_line(vars,
			player,
			wall,
			0x00FF0000);
		i++;
	}
	free(vars->ray);
	vars->ray = NULL;
}
