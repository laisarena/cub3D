/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_scene_description.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 17:52:29 by lfrasson          #+#    #+#             */
/*   Updated: 2021/03/16 02:15:29 by lfrasson         ###   ########.fr       */
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

static int	ft_is_string_number(char *string)
{
	while (*string)
		if (!ft_isdigit(*string++))
			return (0);
	return (1);
}

static int	ft_validate_number(char *string, unsigned int *parameter)
{
	if (!string || !ft_is_string_number(string))
		return (0);
	*parameter = ft_atoi(string);
	return (1);
}

static int	ft_resolution(char **split_line, t_vars *vars)
{
	if (!(ft_validate_number(split_line[1], &vars->scene_description.resolution.x)))
	{
		ft_save_error_message("Misconfiguration on resolution x render size\n", vars);
		return (0);
	}
	if (!(ft_validate_number(split_line[2], &vars->scene_description.resolution.y)))
	{
		ft_save_error_message("Misconfiguration on resolution y render size\n", vars);
		return (0);
	}
	if (split_line[3])
	{
		ft_save_error_message("Misconfiguration on resolution\n", vars);
		return (0);
	}
	vars->scene_description.resolution.identifier = 1;
	vars->scene_description.counter++;
	return (1);
}
static int	ft_texture(char **split_line, t_vars *vars, t_texture *s_texture)
{
	int fd;

	if (split_line[2])
	{
		ft_save_error_message("Misconfiguration on texture\n", vars);
		return (0);
	}
	if ((fd = open(split_line[1], O_RDONLY)) == -1)
	{
		ft_save_error_message(NULL, vars);
		return (0);
	}
	close(fd);
	s_texture->identifier = 1;
	vars->scene_description.counter++;
	return (1);
}

static int	ft_validate_range(int color)
{
	if (color < 0 && color > 255)
		return (-1);
	return (0);
}

static int	ft_color(char **split_line, t_vars *vars, t_color *s_color)
{
	char	**split_color;

	if (split_line[2])
	{
		ft_save_error_message("Misconfiguration on color\n", vars);
		return (0);
	}
	split_color = ft_split(split_line[1], ',');
	if (split_color)
	{
		if (!(ft_validate_number(split_color[0], &s_color->r)))
		{
			free(split_color);
			ft_save_error_message("Misconfiguration on color\n", vars);
			return (0);
		}
		if (!(ft_validate_number(split_color[1], &s_color->g)))
		{
			free(split_color);
			ft_save_error_message("Misconfiguration on color\n", vars);
			return (0);
		}
		if (!(ft_validate_number(split_color[2], &s_color->b)))
		{
			free(split_color);
			ft_save_error_message("Misconfiguration on color\n", vars);
			return(0);
		}
		if (split_color[3])
		{
			free(split_color);
			ft_save_error_message("Misconfiguration on color\n", vars);
			return(0);
		}
	}
	free(split_color);
	if (ft_validate_range(s_color->r) ||
			ft_validate_range(s_color->g) ||
			ft_validate_range(s_color->b))
	{
		ft_save_error_message("Misconfiguration on color\n", vars);
		return (0);
	}
	s_color->identifier = 1;
	vars->scene_description.counter++;
	return (0);
}

static int	validate(char **split_line, t_vars *vars)
{
	if (!ft_strncmp(split_line[0], "R", 2))
		return(ft_resolution(split_line, vars));
	else if (!ft_strncmp(split_line[0], "NO", 3))
		return(ft_texture(split_line, vars, &vars->scene_description.north));
	else if (!ft_strncmp(split_line[0], "SO", 3))
		return(ft_texture(split_line, vars, &vars->scene_description.south));
	else if (!ft_strncmp(split_line[0], "WE", 3))
		return(ft_texture(split_line, vars, &vars->scene_description.west));
	else if (!ft_strncmp(split_line[0], "EA", 3))
		return(ft_texture(split_line, vars, &vars->scene_description.east));
	else if (!ft_strncmp(split_line[0], "S", 2))
		return(ft_texture(split_line, vars, &vars->scene_description.sprite));
	else if (!ft_strncmp(split_line[0], "F", 2))
		return(ft_color(split_line, vars, &vars->scene_description.floor));
	else if (!ft_strncmp(split_line[0], "C", 2))
		return(ft_color(split_line, vars, &vars->scene_description.ceilling));
	return (1);
}

static int	ft_identify_line(char *line,
							t_vars *vars)
{
	char	**split_line;
	int		ret;

	split_line = ft_split(line, ' ');
	if (split_line)
		ret = validate(split_line, vars);
	free(split_line);
	return (ret);
}

int			ft_scene_description_parameters(t_vars *vars)
{
	int				fd;
	unsigned int	column;
	unsigned int	rows;
	char			*line;
	int				ret;

	fd = open(vars->scene_description.file, O_RDONLY);
	line = NULL;
	ret = 0;
	while (get_next_line(fd, &line) > 0 && vars->scene_description.counter <= 8)
		if (line && *line && ret)
			ret = ft_identify_line(line, vars);
	if (!ret)
	{
		free(line);
		return (ret);
	}
	
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
	close(fd);
	free(line);
	if (!ret)
		return (ret);
	return (1);
}

void		ft_check_parameters(t_scene_description *s_scene_description)
{
	if (s_scene_description->resolution.identifier == 0)
		ft_error("Missing R parameter\n");
	if (s_scene_description->north.identifier == 0)
		ft_error("Missing NO parameter\n");
	if (s_scene_description->south.identifier == 0)
		ft_error("Missing SO Parameter\n");
	if (s_scene_description->west.identifier == 0)
		ft_error("Missing WE parameter\n");
	if (s_scene_description->east.identifier == 0)
		ft_error("Missing EA parameter\n");
	if (s_scene_description->sprite.identifier == 0)
		ft_error("Missing S parameter\n");
	if (s_scene_description->floor.identifier == 0)
		ft_error("Missing F parameter\n");
	if (s_scene_description->ceilling.identifier == 0)
		ft_error("Missing C parameter\n");
}
