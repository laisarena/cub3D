/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:44 by lfrasson          #+#    #+#             */
/*   Updated: 2021/01/31 17:04:11 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_error(char *message)
{
	int errnum;

	errnum = errno;
	ft_putstr_fd("Error\n", 1);
	if (!errnum)
		ft_putstr_fd(message, 1);
	else
		printf("%s\n", strerror(errnum));
	exit(-1);
}

static void	validate(char **split_line)
{
	if (!ft_strncmp(split_line[0], "R", 2))
		printf("resolution\n");
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

static void	identify_line(char *line, t_scene_description *scene_description)
{
	char	**split_line;
	split_line = ft_split(line, ' ');
	if (split_line)
		validate(split_line);
	printf("%s\n", split_line[0]);
	printf("%u\n", scene_description->resolution.identifier);
}

static void	take_scene_description_parameters(char *scene_description_file, 
									t_scene_description *s_scene_description)
{
	int		fd;
	char	*line;
	
	fd = open(scene_description_file, O_RDONLY);
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (line)
			identify_line(line, s_scene_description);
		printf("%s\n", line);
	}
	close(fd);
	free(line);
}

int			main(int argc, char **argv)
{
	t_scene_description	s_scene_description;

	errno = 0;
	validate_arguments(argc, argv);
	initialize(&s_scene_description);
	take_scene_description_parameters(argv[1], &s_scene_description); 
	return (0);
}
