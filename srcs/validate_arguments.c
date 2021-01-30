/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:05:44 by lfrasson          #+#    #+#             */
/*   Updated: 2021/01/29 18:45:51 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	verify_save_argument(char *save_argument)
{
	if (ft_strncmp(save_argument, "--save", 7))
		ft_error("The second argument shoud be --save\n");
}

static void	verify_scene_description_path(char *scene_description_file)
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

void		validate_arguments(int argc, char **argv)
{
	if (argc == 1)
		ft_error("This program needs a scene description file as argument\n");
	else if (argc == 2 || argc == 3)
		verify_scene_description_path(argv[1]);
	else
		ft_error("Too many arguments\n");
	if (argc == 3)
		verify_save_argument(argv[2]);
}

