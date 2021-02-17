/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_scene_description.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 17:52:29 by lfrasson          #+#    #+#             */
/*   Updated: 2021/02/03 23:13:49 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int ft_is_map_digit(char c)
{
	if (c == '0'  || c == '1' || c == '2' ||
			c == 'N' || c == 'S' || c == 'E' ||c == 'W')
		return (1);
	return (0);
}

static int	ft_is_map_line(char *string)
{
	while (*string)
		if (!ft_is_map_digit(*string++))
			return (0);
	return (1);
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
		return (-1);
	*parameter = ft_atoi(string);
	return (0);
}

static int	ft_resolution(char **split_line, t_resolution *s_resolution,
							unsigned int *counter)
{
	if (ft_validate_number(split_line[1], &s_resolution->x))
		ft_error("Misconfiguration on resolution x render size\n");
	if (ft_validate_number(split_line[2], &s_resolution->y))
		ft_error("Misconfiguration on resolution y render size\n");
	if (split_line[3])
		ft_error("Misconfiguration on resolution\n");
	s_resolution->identifier = 1;
	counter++;
	return (0);
}

static int	ft_texture(char **split_line, t_texture *s_texture,
							unsigned int *counter)
{
	int fd;

	if (split_line[2])
		ft_error("Misconfiguration on texture\n");
	if ((fd = open(split_line[1], O_RDONLY)) == -1)
		ft_error(NULL);
	else
		close(fd);
	s_texture->identifier = 1;
	counter++;
	return (0);
}

static int	ft_validate_range(unsigned int color)
{
	if (color < 0 && color > 255)
		return (-1);
	return (0);
}

static int	ft_color(char **split_line, t_color *s_color, unsigned int *counter)
{
	char	**split_color;

	if (split_line[2])
		ft_error("Misconfiguration on color\n");
	split_color = ft_split(split_line[1], ',');
	if (split_color)
	{
		if (ft_validate_number(split_color[0], &s_color->r))
			ft_error("Misconfiguration on color\n");
		if (ft_validate_number(split_color[1], &s_color->g))
			ft_error("Misconfiguration on color\n");
		if (ft_validate_number(split_color[2], &s_color->b))
			ft_error("Misconfiguration on color\n");
		if (split_color[3])
			ft_error("Misconfiguration on color\n");
	}
	if (ft_validate_range(s_color->r) ||
			ft_validate_range(s_color->g) ||
			ft_validate_range(s_color->b))
		ft_error("Misconfiguration on color\n");
	s_color->identifier = 1;
	counter++;
	return (0);
}

static void	validate(char **split_line,
						t_scene_description *s_scene_description)
{
	if (!ft_strncmp(split_line[0], "R", 2))
		ft_resolution(split_line, &s_scene_description->resolution,
									&s_scene_description->counter);
	else if (!ft_strncmp(split_line[0], "NO", 3))
		ft_texture(split_line, &s_scene_description->north,
									&s_scene_description->counter);
	else if (!ft_strncmp(split_line[0], "SO", 3))
		ft_texture(split_line, &s_scene_description->south,
									&s_scene_description->counter);
	else if (!ft_strncmp(split_line[0], "WE", 3))
		ft_texture(split_line, &s_scene_description->west,
									&s_scene_description->counter);
	else if (!ft_strncmp(split_line[0], "EA", 3))
		ft_texture(split_line, &s_scene_description->east,
									&s_scene_description->counter);
	else if (!ft_strncmp(split_line[0], "S", 2))
		ft_texture(split_line, &s_scene_description->sprite,
									&s_scene_description->counter);
	else if (!ft_strncmp(split_line[0], "F", 2))
		ft_color(split_line, &s_scene_description->floor,
									&s_scene_description->counter);
	else if (!ft_strncmp(split_line[0], "C", 2))
		ft_color(split_line, &s_scene_description->ceilling,
									&s_scene_description->counter);
}

static void	ft_identify_line(char *line, t_scene_description *s_scene_description)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (split_line)
		validate(split_line, s_scene_description);
}

void		ft_check_parameters(t_scene_description *s_scene_description)
{
	if (s_scene_description->resolution.identifier == 0)
		ft_error("Missing R parameter");
	if (s_scene_description->north.identifier == 0)
		ft_error("Missing NO parameter");
	if (s_scene_description->south.identifier == 0)
		ft_error("Missing SO Parameter");
	if (s_scene_description->west.identifier == 0)
		ft_error("Missing WE parameter");
	if (s_scene_description->east.identifier == 0)
		ft_error("Missing EA parameter");
	if (s_scene_description->sprite.identifier == 0)
		ft_error("Missing S parameter");
	if (s_scene_description->floor.identifier == 0)
		ft_error("Missing F parameter");
	if (s_scene_description->ceilling.identifier == 0)
		ft_error("Missing C arameter");
}

void		ft_scene_description_parameters(char *scene_description_file,
									t_scene_description *s_scene_description)
{
	int		fd;
	char	*line;

	fd = open(scene_description_file, O_RDONLY);
	line = NULL;
	while (get_next_line(fd, &line) > 0 && s_scene_description->counter <= 8)
		if (line && *line)
			ft_identify_line(line, s_scene_description);
	ft_check_parameters(s_scene_description);
	while (get_next_line(fd, &line))
		ft_is_map_line(line);
	close(fd);
	free(line);
}
