/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 19:59:40 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 17:47:51 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_add_visible_sprite(t_list **list, t_sprite *sprite)
{
	t_list		*tmp;
	t_list		*new;
	t_list		*previous;
	t_sprite	*sp;

	new = ft_lstnew(sprite);
	tmp = *list;
	previous = *list;
	while (tmp)
	{
		sp = tmp->content;
		if (sprite->distance > sp->distance)
		{
			new->next = tmp;
			if (tmp == *list)
				*list = new;
			else
				previous->next = new;
			return ;
		}
		previous = tmp;
		tmp = tmp->next;
	}
	ft_lstadd_back(list, new);
}

void	ft_free_list(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = tmp->next;
		free(tmp);
	}
	*lst = NULL;
}

static float	ft_calc_sprite_angle(t_sprite *sprite, t_player player)
{
	float	angle;
	float	relative_angle;

	angle = atan2(sprite->position.y - player.y,
			sprite->position.x - player.x);
	relative_angle = player.rotation_angle - angle;
	if (relative_angle > PI)
		relative_angle -= TWO_PI;
	if (relative_angle < -PI)
		relative_angle += TWO_PI;
	sprite->angle = relative_angle;
	return (fabs(relative_angle));
}

void	ft_define_visible_sprites(t_vars *vars)
{
	t_list		*sprite_list;
	t_sprite	*sprite;
	float		relative_angle;	

	sprite_list = vars->game.sprites.list;
	while (sprite_list)
	{
		sprite = sprite_list->content;
		relative_angle = ft_calc_sprite_angle(sprite, vars->player);
		if (relative_angle < (FOV_ANGLE / 2) + 0.2)
		{
			sprite->visible = 1;
			sprite->distance = ft_distance_between_points(
					sprite->position.x,
					sprite->position.y,
					vars->player.x,
					vars->player.y);
			ft_add_visible_sprite(&vars->game.sprites.list_visible,
				sprite_list->content);
		}
		else
			sprite->visible = 0;
		sprite_list = sprite_list->next;
	}
}
