/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 19:59:40 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/14 20:44:39 by lfrasson         ###   ########.fr       */
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

static float	ft_calc_sprite_angle(t_sprite *sprite, t_player player)
{
	float	angle;
	float	relative_angle;

	angle = atan2(sprite->position.y - player.y,
			sprite->position.x - player.x);
	relative_angle = player.rotation_angle - angle;
	sprite->angle = relative_angle;
	if (relative_angle > PI)
		relative_angle -= TWO_PI;
	if (relative_angle < -PI)
		relative_angle += TWO_PI;
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

float	ft_calc_top(int win_hight, int height);
float	ft_calc_bottom(int win_height, int height);
int		ft_get_color(t_image_data *image, int x, int y);

typedef struct s_sprite_proj
{
	float	width;
	float	height;
	float	top;
	float	bottom;
	float	left;
	float	right;
	float	x_position;
	float	pixel_width;
	float	stretch_factor;
	int		texture_offset_x;
	int		texture_offset_y;

}			t_sprite_proj;

static t_sprite_proj	ft_calc_projection_parameters(t_sprite *sprite,
		t_vars *vars)
{
	t_sprite_proj	projection;

	projection.height = (TILE / sprite->distance) * vars->proj_plane_distance;
	projection.width = projection.height;
	projection.top = ft_calc_top(
			vars->game.resolution.height,
			projection.height);
	projection.bottom = ft_calc_bottom(
			vars->game.resolution.height,
			projection.height);
	projection.x_position = tan(-sprite->angle) * vars->proj_plane_distance;
	projection.left = (vars->game.resolution.width / 2)
		+ projection.x_position - (projection.width / 2);
	projection.right = projection.left + projection.width;
	projection.pixel_width = vars->game.sprites.texture.width
		/ projection.width;
	projection.stretch_factor = (float)vars->game.sprites.texture.height
		/ projection.height;
	return (projection);
	//projection.height = (vars->game.sprites.texture.height / sprite->distance)
	//	* vars->proj_plane_distance;
}

static void	ft_render_sprite_column(int x, t_sprite *sprite,
		t_sprite_proj projection, t_vars *vars)
{
	int		y;
	int		distance_from_top;
	int		color;

	y = projection.top;
	while (y < projection.bottom)
	{
		if (x > 0 && x < vars->game.resolution.width
			&& y > 0 && vars->game.resolution.height)
		{
			distance_from_top = y + (projection.height / 2)
				- (vars->game.resolution.height / 2);
			projection.texture_offset_y = distance_from_top
				* projection.stretch_factor;
			color = ft_get_color(
					&vars->game.sprites.texture.image,
					projection.texture_offset_x,
					projection.texture_offset_y);
			if (sprite->distance < vars->ray[x].distance && color != 0)
				ft_put_pixel(&vars->image, x, y, color);
		}
		y++;
	}
}

static void	ft_render_sprite(t_sprite *sprite,
		t_sprite_proj projection, t_vars *vars)
{
	int		x;

	x = projection.left;
	while (x < projection.right)
	{
		projection.texture_offset_x = (x - projection.left)
			* projection.pixel_width;
		ft_render_sprite_column(x, sprite, projection, vars);
		x++;
	}
}

void	ft_render_sprites_projection(t_vars *vars)
{
	t_list			*list;
	t_sprite		*sprite;
	t_sprite_proj	projection;

	list = vars->game.sprites.list_visible;
	while (list)
	{
		sprite = list->content;
		projection = ft_calc_projection_parameters(sprite, vars);
		ft_render_sprite(sprite, projection, vars);
		list = list->next;
	}
	ft_free_list(&vars->game.sprites.list_visible);
}
