/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_scene_description.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 17:52:29 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 15:06:13 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate(char **split_line, t_vars *vars)
{
	if (!ft_strncmp(split_line[0], "R", 2))
		return (ft_resolution(split_line, vars));
	else if (!ft_strncmp(split_line[0], "NO", 3))
		return (ft_texture(split_line, vars, &vars->game.north));
	else if (!ft_strncmp(split_line[0], "SO", 3))
		return (ft_texture(split_line, vars, &vars->game.south));
	else if (!ft_strncmp(split_line[0], "WE", 3))
		return (ft_texture(split_line, vars, &vars->game.west));
	else if (!ft_strncmp(split_line[0], "EA", 3))
		return (ft_texture(split_line, vars, &vars->game.east));
	else if (!ft_strncmp(split_line[0], "S", 2))
		return (ft_texture(split_line, vars, &vars->game.sprites.texture));
	else if (!ft_strncmp(split_line[0], "F", 2))
		return (ft_color(split_line, vars, &vars->game.floor));
	else if (!ft_strncmp(split_line[0], "C", 2))
		return (ft_color(split_line, vars, &vars->game.ceilling));
	return (1);
}

static int	ft_identify_line(char *line, t_vars *vars)
{
	char	**split_line;
	int		ret;

	split_line = ft_split(line, ' ');
	ft_free_null(line);
	ret = 1;
	if (split_line)
		ret = validate(split_line, vars);
	ft_free_split(split_line);
	return (ret);
}

static int	ft_parameters(int fd, t_vars *vars)
{
	char	*line;
	int		ret;

	line = NULL;
	ret = 1;
	while (vars->game.counter < 8 && ret && get_next_line(fd, &line) > 0)
	{
		if (line && *line)
			ret = ft_identify_line(line, vars);
		else
			free(line);
		line = NULL;
	}
	free(line);
	return (ret);
}

int	ft_scene_description_parameters(t_vars *vars)
{
	int	fd;

	fd = open(vars->game.file, O_RDONLY);
	if (!(ft_parameters(fd, vars)))
	{
		close(fd);
		return (1);
	}
	ft_map(fd, vars);
	close(fd);
	return (0);
}
