/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_edges.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 15:47:55 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 22:05:00 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_is_matrix_edge(int i, int j, int row, int column)
{
	if (i == 0 || j == 0 || i == row - 1 || j == column -1)
		return (1);
	return (0);
}

static int	ft_is_char_edge(char c)
{
	if (c == ' ' || c == '1' || c == '\0')
		return (1);
	return (0);
}

static int	ft_is_invalid_edge(int i, int j, t_map *map)
{
	if (!(ft_is_matrix_edge(i, j, map->rows, map->cols)))
		return (0);
	return (!ft_is_char_edge(map->matrix[i][j]));
}

static int	ft_is_invalid_outside(int row, int col, t_map *map)
{
	int	i;
	int	j;

	if (map->matrix[row][col] != ' ' && map->matrix[row][col] != '\0')
		return (0);
	i = row - 1;
	if (i < 0)
		i = row;
	while (i <= row + 1 && i < map->rows)
	{
		j = col - 1;
		if (j < 0)
			j = col;
		while (j <= col + 1 && j < map->cols)
		{
			if (!ft_is_char_edge(map->matrix[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_validate_edges(t_map *map, t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (ft_is_invalid_edge(i, j, map))
				ft_error("Invalid map\n", vars);
			if (ft_is_invalid_outside(i, j, map))
				ft_error("Invalid map\n", vars);
			j++;
		}
		i++;
	}
}
