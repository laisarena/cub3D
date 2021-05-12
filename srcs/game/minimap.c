/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:56:33 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/12 21:37:07 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_is_wall_at(float x, float y, t_vars *vars)
{
	int		map_row;
	int		map_column;
	char	var;

	if (x < 0 || x > vars->map.cols * TILE
		|| y < 0 || y > vars->map.rows * TILE)
		return (1);
	map_row = floor(y / TILE);
	map_column = floor(x / TILE);
	var = vars->map.matrix[map_row][map_column];
	return (var == '1');
}

void	ft_render_minimap_sprites(t_vars *vars)
{
	t_list		*sprite_list;
	t_sprite	*sprite;
	t_retangle	retangle;

	sprite_list = vars->game.sprites.list;
	while (sprite_list)
	{
		sprite = sprite_list->content;
		retangle.position = sprite->position;
		retangle.width = 2;
		retangle.height = 2;
		retangle.position.x *= MINI_FACTOR;
		retangle.position.y *= MINI_FACTOR;
		if (sprite->visible)
			ft_rectangle_on_image(vars, retangle, 0xFF00FFFF);
		else
			ft_rectangle_on_image(vars, retangle, 0xFF444444);
		sprite_list = sprite_list->next;
	}
}

void	ft_render_minimap_grid(t_vars *vars)
{
	int			i;
	int			j;
	int			color;
	float		tile;
	t_retangle	retangle;

	tile = MINI_FACTOR * TILE;
	retangle.width = tile;
	retangle.height = tile;
	i = 0;
	while (i < vars->map.rows)
	{
		retangle.position.y = tile * i;
		j = 0;
		while (j < vars->map.cols)
		{
			if (vars->map.matrix[i][j] == '1')
				color = 0x00FFFFFF;
			else
				color = 0x00000000;
			retangle.position.x = tile * j++;
			ft_rectangle_on_image(vars, retangle, color);
		}
		i++;
	}
}
