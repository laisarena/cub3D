/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:32:50 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/28 20:34:52 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_key_press(int keycode, t_vars *vars)
{
	if (keycode == 0xFF1B)
		ft_close(vars);
	if (keycode == W)
		vars->player.walk_direction = 1;
	if (keycode == A)
		vars->player.turn_direction = -1;
	if (keycode == S)
		vars->player.walk_direction = -1;
	if (keycode == D)
		vars->player.turn_direction = 1;
	ft_render(vars);
	return (1);
}

void	ft_reset_moviments(t_player *player)
{
	player->turn_direction = 0;
	player->walk_direction = 0;
}

void	ft_move_player(t_vars *vars)
{
	float	x;
	float	y;
	float	step;

	vars->player.rotation_angle += vars->player.turn_direction * ROT_SPEED;
	step = vars->player.walk_direction * WALK_SPEED;
	x = vars->player.x + cos(vars->player.rotation_angle) * step;
	y = vars->player.y + sin(vars->player.rotation_angle) * step;
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
