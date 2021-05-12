/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 19:59:40 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/13 00:18:22 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_define_visible_sprites(t_vars *vars)
{
	t_list		*sprite_list;
	t_sprite	*sprite;
	float		sprite_player_angle;	

	sprite_list = vars->game.sprites.list;
	while (sprite_list)
	{
		sprite = sprite_list->content;
		float ang;
		ang = atan2(sprite->position.x - vars->player.x,
					sprite->position.y - vars->player.y) - (PI / 2);
		printf("sprite %f\n", ang * 180 / PI);
		printf("player %f\n", vars->player.rotation_angle * 180 / PI);
		sprite_player_angle = vars->player.rotation_angle + ang;
		if (sprite_player_angle > PI)
			sprite_player_angle -= TWO_PI;
		if (sprite_player_angle < - PI)
			sprite_player_angle += TWO_PI;
		sprite_player_angle = fabs(sprite_player_angle);
		if (sprite_player_angle < FOV_ANGLE / 2)
		{
			sprite->visible = 1;
			sprite->angle = sprite_player_angle;
			sprite->distance = ft_distance_between_points(
					sprite->position.x,
					sprite->position.y,
					vars->player.x,
					vars->player.y);
			//ft_add_visible_sprite(vars, sprites_list->content);
		}
		else
			sprite->visible = 0;
		sprite_list = sprite_list->next;
	}
}

//void	ft_render_sprites(t_vars *vars)
