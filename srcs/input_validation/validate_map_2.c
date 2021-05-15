/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 01:58:13 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/15 21:01:41 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

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

static void	ft_check_player(char c, int i, int j, t_vars *vars)
{
	if (!ft_is_player(c))
		return ;
	if (vars->player.set)
		ft_error("More then one player position\n");
	vars->player.set++;
	vars->player.x = j;
	vars->player.y = i;
	if (c == 'N')
		vars->player.rotation_angle = 1.5 * PI;
	else if (c == 'S')
		vars->player.rotation_angle = 0.5 * PI;
	else if (c == 'E')
		vars->player.rotation_angle = 0;
	else if (c == 'W')
		vars->player.rotation_angle = PI;
}

static void	ft_check_sprite(char c, int i, int j, t_vars *vars)
{
	t_sprite	*sprite;

	if (c != '2')
		return ;
	sprite = (t_sprite *)malloc(sizeof(t_sprite));
	sprite->position.x = j;
	sprite->position.y = i;
	ft_lstadd_back(&vars->game.sprites.list, ft_lstnew(sprite));
}

static int	ft_validate_edges(t_map *map)
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
				return (-1);
			if (ft_is_invalid_outside(i, j, map))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_check_map(t_vars *vars)
{
	int	i;
	int	j;

	if (ft_validate_edges(&vars->map))
		ft_error("Invalid map\n");
	i = 0;
	while (i < vars->map.rows)
	{
		j = 0;
		while (j < vars->map.cols)
		{
			ft_check_player(vars->map.matrix[i][j], i, j, vars);
			ft_check_sprite(vars->map.matrix[i][j], i, j, vars);
			j++;
		}
		i++;
	}
	if (!vars->player.set)
		ft_error("No player position\n");
}
