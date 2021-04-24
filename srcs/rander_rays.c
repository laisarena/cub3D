/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 23:22:33 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/23 23:32:44 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rende_rays(t_vars *vars)
{
	int i;

	i = 0;
	while(i < vars->scene_description.resolution.x)
	{
		ft_draw_line(vars,
			vars->player.x * MINI_FACTOR,
			vars->player.y * MINI_FACTOR,
			vars->ray[i].wall_hit.x * MINI_FACTOR,
			vars->ray[i].wall_hit.y * MINI_FACTOR,
			0x00FF0000);
		i++;
	}
}
