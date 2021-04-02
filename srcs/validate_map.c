/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:49:43 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/02 22:06:46 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_is_map_digit(char c)
{
	if (c == '0' || c == '1' || c == '2' ||
			c == 'N' || c == 'S' || c == 'E' ||c == 'W')
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

int			ft_map(int fd, t_vars *vars)
{
	unsigned int	column;
	unsigned int	rows;
	char			*line;
	int				ret;

	line = NULL;
	ret = 1;
	rows = 0;
	while (get_next_line(fd, &line))
	{
		if (!(column = ft_is_map_line(line)))
		{
			ret = 0;
			ft_save_error_message("Invalid map grid\n", vars);
		}
		if (column > vars->scene_description.map.cols)
			vars->scene_description.map.cols = column;
		rows++;
	}
	free(line);
	return (ret);
}

