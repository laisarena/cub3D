/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 17:36:26 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 17:45:58 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_sprite_proj	ft_calc_projection_parameters(t_sprite *sprite,
		t_vars *vars)
{
	t_sprite_proj	projection;
	float			perp_distance;

	perp_distance = sprite->distance * cos(sprite->angle);
	projection.height = (TILE / perp_distance) * vars->proj_plane_distance;
	projection.width = projection.height;
	projection.top = ft_calc_top(
			vars->game.resolution.height,
			projection.height);
	projection.bottom = ft_calc_bottom(
			vars->game.resolution.height,
			projection.height);
	projection.x_position = tan(sprite->angle) * vars->proj_plane_distance;
	projection.left = (vars->game.resolution.width / 2)
		- projection.x_position - (projection.width / 2);
	projection.right = projection.left + projection.width;
	projection.pixel_width = vars->game.sprites.texture.width
		/ projection.width;
	projection.stretch_factor = (float)vars->game.sprites.texture.height
		/ projection.height;
	return (projection);
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

	x = ceil(projection.left);
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
