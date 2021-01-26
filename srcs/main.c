/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:44 by lfrasson          #+#    #+#             */
/*   Updated: 2021/01/29 15:40:05 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

static void	ft_error(char *message)
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

static void	verify_save_argument(char *save_argument)
{
	if (ft_strncmp(save_argument, "--save", 7))
		ft_error("The second argument shoud be --save\n");
}

static void	verify_scene_description_file(char *scene_description_file)
{
	int		len;
	int		fd;
	char	*extension;

	len = ft_strlen(scene_description_file);
	extension = ft_strnstr(scene_description_file, ".cub", len);
	if (!extension || ft_strncmp(extension, ".cub", 5))
		ft_error("The scene description file must have the .cub extension\n");
	if ((fd = open(scene_description_file, O_RDONLY)) == -1)
		ft_error(NULL);
	else
		close(fd);
}

static void	validate_arguments(int argc, char **argv)
{
	if (argc == 1)
		ft_error("This program needs a scene description file as argument\n");
	else if (argc == 2 || argc == 3)
		verify_scene_description_file(argv[1]);
	else
		ft_error("Too many arguments\n");
	if (argc == 3)
		verify_save_argument(argv[2]);
}

int			main(int argc, char **argv)
{
	errno = 0;
	validate_arguments(argc, argv);
	return (0);
}
