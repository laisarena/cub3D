/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:32:50 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/28 19:55:52 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_reset_moviments(t_player *player)
{
	player->turn_direction = 0;
	player->walk_direction_x = 0;
	player->walk_direction_y = 0;
}

void	ft_move_player(t_vars *vars)
{
	float	x;
	float	y;

	vars->player.rotation_angle += vars->player.turn_direction * ROT_SPEED;
	x = vars->player.x + vars->player.walk_direction_x * WALK_SPEED;
	y = vars->player.y + vars->player.walk_direction_y * WALK_SPEED;
	if (!ft_is_wall_at(x, y, vars))
	{
		vars->player.x = x;
		vars->player.y = y;
	}
}

void	ft_render_player(t_vars *vars)
{
	t_retangle	retangle;

	retangle.width =vars->player.width * MINI_FACTOR;
	retangle.height = vars->player.height * MINI_FACTOR;
	retangle.position.x = vars->player.x * MINI_FACTOR;
	retangle.position.y = vars->player.y * MINI_FACTOR;
	ft_rectangle_on_image(vars, retangle, 0x00FF0000);
}
