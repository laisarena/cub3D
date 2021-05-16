/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 15:26:30 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 22:03:28 by lfrasson         ###   ########.fr       */
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

static int	ft_is_empty_after_map(int fd, t_vars *vars)
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
		ft_free_null(line);
	}
	free(line);
	return (ret);
}

void	ft_create_map_list(int fd, char *line, t_list **map_list, t_vars *vars)
{
	int		column;
	int		is_map;

	is_map = 0;
	while (get_next_line(fd, &line))
	{
		if (*line)
		{
			is_map = 1;
			column = ft_is_map_line(line);
			if (!column)
				ft_exit(fd, line, map_list, vars);
			else if (column > vars->map.cols)
				vars->map.cols = column;
			ft_lstadd_back(map_list, ft_lstnew(line));
			vars->map.rows++;
		}
		else
		{
			ft_free_null(line);
			if (is_map && !ft_is_empty_after_map(fd, vars))
				ft_exit(fd, line, map_list, vars);
		}
	}
	ft_free_null(line);
}
