/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_scene_description.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 17:52:29 by lfrasson          #+#    #+#             */
/*   Updated: 2021/01/31 19:22:54 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	resolution(char **split_line, t_resolution *s_resolution)
{
	if (ft_validate_number(split_line[1], &s_resolution->x))
		ft_error("Misconfiguration on resolution x render size\n");
	if (ft_validate_number(split_line[2], &s_resolution->y))
		ft_error("Misconfiguration on resolution y render size\n");
	if (split_line[3])
		ft_error("Misconfiguration on resolution\n");
	s_resolution->identifier = 1;
	return (0);
}

static void	validate(char **split_line,
						t_scene_description *s_scene_description)
{
	if (!ft_strncmp(split_line[0], "R", 2))
		resolution(split_line, &s_scene_description->resolution);
	else if (!ft_strncmp(split_line[0], "NO", 3))
		printf("texture\n");
	else if (!ft_strncmp(split_line[0], "SO", 3))
		printf("texture\n");
	else if (!ft_strncmp(split_line[0], "WE", 3))
		printf("texture\n");
	else if (!ft_strncmp(split_line[0], "EA", 3))
		printf("texture\n");
	else if (!ft_strncmp(split_line[0], "S", 2))
		printf("texture\n");
	else if (!ft_strncmp(split_line[0], "F", 2))
		printf("color\n");
	else if (!ft_strncmp(split_line[0], "C", 2))
		printf("color\n");
}

static void	identify_line(char *line, t_scene_description *s_scene_description)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (split_line)
		validate(split_line, s_scene_description);
}

void		take_scene_description_parameters(char *scene_description_file,
									t_scene_description *s_scene_description)
{
	int		fd;
	char	*line;

	fd = open(scene_description_file, O_RDONLY);
	line = NULL;
	while (get_next_line(fd, &line) > 0)
		if (line && *line)
			identify_line(line, s_scene_description);
	close(fd);
	free(line);
}
