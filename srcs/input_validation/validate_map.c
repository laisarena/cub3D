/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:49:43 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 15:34:32 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_create_matrix(t_map *map)
{
	map->matrix = malloc(sizeof(char *) * (map->rows + 1));
	if (!map->matrix)
		return ;
	map->matrix[map->rows] = NULL;
}

static void	ft_list_to_matrix(t_list *list, t_map *map)
{
	int		i;
	int		j;
	char	*line;
	t_list	*tmp;

	i = 0;
	tmp = list;
	while (tmp)
	{
		map->matrix[i] = malloc(sizeof(char) * (map->cols + 1));
		if (!map->matrix[i])
			return ;
		line = tmp->content;
		j = 0;
		while (*line)
			map->matrix[i][j++] = *line++;
		while (j < map->cols)
			map->matrix[i][j++] = ' ';
		map->matrix[i][map->cols] = '\0';
		tmp = tmp->next;
		i++;
	}
}

int	ft_map(int fd, t_vars *vars)
{
	char	*line;
	t_list	*map_list;

	line = NULL;
	map_list = NULL;
	ft_create_map_list(fd, line, &map_list, vars);
	ft_create_matrix(&vars->map);
	ft_list_to_matrix(map_list, &vars->map);
	ft_lstclear(&map_list, &ft_del);
	ft_free_null(line);
	return (1);
}
