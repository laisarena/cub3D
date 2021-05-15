/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:49:43 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/15 22:36:25 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_is_map_digit(char c)
{
	if (c == ' ' || c == '0' || c == '1' || c == '2'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int	ft_is_map_line(char *string)
{
	int	cols;

	cols = 0;
	while (string[cols])
		if (!ft_is_map_digit(string[cols++]))
			return (0);
	return (cols);
}

static void	ft_list_to_matix(t_list *list, t_map *map)
{
	int		i;
	int		j;
	char	*line;

	map->matrix = malloc(sizeof(char *) * (map->rows + 1));
	if (!map->matrix)
		return ;
	map->matrix[map->rows] = NULL;
	i = 0;
	while (list)
	{
		map->matrix[i] = malloc(sizeof(char) * (map->cols + 1));
		if (!map->matrix[i])
			return ;
		line = list->content;
		j = 0;
		while (*line)
			map->matrix[i][j++] = *line++;
		while (j < map->cols)
			map->matrix[i][j++] = ' ';
		map->matrix[i][map->cols] = '\0';
		list = list->next;
		i++;
	}
}

void	ft_del(void *pointer)
{
	free(pointer);
}

int	ft_is_empty_after_map(int fd, t_vars *vars)
{
	char	*line;
	int		ret;

	ret = 1;
	line = NULL;
	while (get_next_line(fd, &line))
	{
		if (!*line)
		{
			ft_save_error_message("Invalid map\n", vars);
			ret = 0;
		}
	}
	return (ret);
}

int	ft_map(int fd, t_vars *vars)
{
	int		column;
	char	*line;
	int		ret;
	int		is_map;
	t_list	*map_list;

	line = NULL;
	ret = 1;
	is_map = 0;
	map_list = NULL;
	while (get_next_line(fd, &line))
	{
		if (*line)
		{
			is_map = 1;
			column = ft_is_map_line(line);
			if (!column)
			{
				ft_save_error_message("Invalid map\n", vars);
				ret = 0;
				break ;
			}
			else if (column > vars->map.cols)
				vars->map.cols = column;
			ft_lstadd_back(&map_list, ft_lstnew(line));
			vars->map.rows++;
		}
		else
		{
			free(line);
			line = NULL;
			if (is_map)
				ret = ft_is_empty_after_map(fd, vars);
		}
	}
	ft_list_to_matix(map_list, &vars->map);
	ft_lstclear(&map_list, &ft_del);
	free(line);
	return (ret);
}
