/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 19:59:40 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/13 21:03:04 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_add_visible_sprite(t_list **list, t_sprite *sprite)
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
		if (sprite->distance < sp->distance)
		{
			new->next = tmp;
			previous->next = new;
			return ;
		}
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
			ft_add_visible_sprite(&vars->game.sprites.list_visible,
					sprite_list->content);
		}
		else
			sprite->visible = 0;
		sprite_list = sprite_list->next;
	}
}

float	ft_calc_wall_top(int win_hight, int wall_height);
float	ft_calc_wall_bottom(int win_height, int wall_height);
void	ft_render_sprites(t_vars *vars)
{
	t_list		*list;
	t_sprite	*sprite;
	float		width;
	float		height;
	float		top;
	float		bottom;

	list = vars->game.sprites.list_visible;
	while (list)
	{
		sprite = list->content;
		height = (vars->game.sprites.texture.height / sprite->distance)
			* vars->proj_plane_distance;
		width = height;
		top = ft_calc_wall_top(vars->game.resolution.height, height);
		bottom = ft_calc_wall_bottom(vars->game.resolution.height, height);
		
		int y = top;
		while (y < bottom)
		{
			ft_put_pixel(&vars->image, 0, y, 0xFFFF0000);
			ft_put_pixel(&vars->image, 1, y, 0xFFFF0000);
			ft_put_pixel(&vars->image, 2, y, 0xFFFF0000);
			ft_put_pixel(&vars->image, 3, y, 0xFFFF0000);
			ft_put_pixel(&vars->image, 4, y, 0xFFFF0000);
			y++;
		}
		list = list->next;	
		width++;
	}
	ft_free_list(&vars->game.sprites.list_visible);
}
