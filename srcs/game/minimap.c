/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:56:33 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/28 19:26:33 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_is_wall_at(float x, float y, t_vars *vars)
{
	int		map_row;
	int		map_column;
	char	var;

	//if (x < 0 || x > vars->scene_description.resolution.x
	//	|| y < 0 || y > vars->scene_description.resolution.y)
	if (x < 0 || x > vars->map.cols * TILE
		|| y < 0 || y > vars->map.rows * TILE)
		return (1);
	map_row = floor(y / TILE);
	map_column = floor(x / TILE);
	var = vars->map.matrix[map_row][map_column];
	return (var == '1');
}

void	ft_render_minimap(t_vars *vars)
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
