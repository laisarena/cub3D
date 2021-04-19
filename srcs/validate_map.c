/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:49:43 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/19 03:00:55 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_is_map_digit(char c)
{
	if (c == ' ' || c == '0' || c == '1' || c == '2' ||
			c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int	ft_is_map_line(char *string)
{
	int cols;

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

	if (!(map->matrix = malloc(sizeof(char *) * (map->rows + 1))))
		return ;
	map->matrix[map->rows] = NULL;
	i = 0;
	while (list)
	{
		if (!(map->matrix[i] = malloc(sizeof(char) * (map->cols + 1))))
			return ;
		line = list->content;
		j = 0;
		while (*line)
			map->matrix[i][j++] = *line++;
		map->matrix[i][map->cols] = '\0';
		list = list->next;
		i++;
	}
}

void		ft_del(void *pointer)
{
	free(pointer);
}

int			ft_map(int fd, t_vars *vars)
{
	int		column;
	int		rows;
	char	*line;
	int		ret;
	t_list	*map_list;

	line = NULL;
	ret = 1;
	rows = 0;
	map_list = NULL;
	while (get_next_line(fd, &line) && ret)
	{
		if (*line)
		{
			if (!(column = ft_is_map_line(line)))
			{
				ft_save_error_message("Invalid map grid\n", vars);
				ret = 0;
			} else if (column > vars->map.cols)
				vars->map.cols = column;
			ft_lstadd_back(&map_list, ft_lstnew(line));
			rows++;
		}
		else
		{
			free(line);
			line = NULL;
		}
	}
	vars->map.rows = rows;
	ft_list_to_matix(map_list, &vars->map);
	ft_lstclear(&map_list, &ft_del);
	free(line);
	return (ret);
}
