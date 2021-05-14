/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 19:59:40 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/14 02:52:42 by lfrasson         ###   ########.fr       */
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
		if (sprite->distance > sp->distance)
		{
			new->next = tmp;
			if (previous == *list)
				*list = new;
			else
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
int	ft_get_color(t_image_data *image, int x, int y);
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
		float	angle = atan2(sprite->position.y - vars->player.y, 
				sprite->position.x- vars->player.x) - vars->player.rotation_angle;
		float sprite_pos_x = tan(angle) * vars->proj_plane_distance;
		float sprite_left = (vars->game.resolution.width / 2) + sprite_pos_x
			- (width / 2 );
		float sprite_right = sprite_left + width; 
		int offset_x;
		int offset_y;
		int x = sprite_left;
		while (x < sprite_right)
		{
			float texel_width = (vars->game.sprites.texture.width / width);
			offset_x = (x - sprite_left) * texel_width;
			int y = top;
			int		distance_from_top;
			float	stretch_factor;
			while (y < bottom)
			{
				if (x > 0 && x < vars->game.resolution.width
						&& y > 0 && vars->game.resolution.height)
				{
					distance_from_top = y + (height / 2) - (vars->game.resolution.height / 2);
					stretch_factor = (float)vars->game.sprites.texture.height / height;
					offset_y = distance_from_top * stretch_factor;
					int color = ft_get_color(&vars->game.sprites.texture.image,
							offset_x, offset_y);
					if (sprite->distance < vars->ray[x].distance && color != 0)
						ft_put_pixel(&vars->image, x, y, color);
				}
				y++;
			}
			x++;
		}
		list = list->next;	
		width++;
	}
	ft_free_list(&vars->game.sprites.list_visible);
}
