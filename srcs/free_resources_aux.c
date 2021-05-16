/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:02:00 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 21:50:13 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_null(void *pointer)
{
	if (pointer)
		free(pointer);
	pointer = NULL;
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		ft_free_null(split[i++]);
	ft_free_null(split);
}

void	ft_del(void *pointer)
{
	free(pointer);
}

static void	ft_close_file(int fd)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line))
		ft_free_null(line);
	free(line);
	close(fd);
}

void	ft_exit(int fd, char *line, t_list **map_list, t_vars *vars)
{
	ft_close_file(fd);
	ft_lstclear(map_list, &ft_del);
	free(line);
	ft_error("Invalid map\n", vars);
}
