/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:05:44 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/09 20:14:53 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_check_save_argument(char *save_argument)
{
	if (ft_strncmp(save_argument, "--save", 7))
		ft_error("The second argument shoud be --save\n");
	return (1);
}

static void	ft_check_file_path_argument(char *scene_description_file)
{
	int		len;
	int		fd;
	char	*extension;

	len = ft_strlen(scene_description_file);
	extension = ft_strnstr(scene_description_file, ".cub", len);
	if (!extension || ft_strncmp(extension, ".cub", 5))
		ft_error("The scene description file must have the .cub extension\n");
	fd = open(scene_description_file, O_RDONLY);
	if (!fd)
		ft_error(NULL);
	else
		close(fd);
}

void	ft_validate_arguments(int argc, char **argv, t_vars *vars)
{
	if (argc == 1)
		ft_error("This program needs a file .cub as first argument\n");
	else if (argc > 3)
		ft_error("Too many arguments\n");
	vars->bmp_save = 0;
	if (argc == 3)
		vars->bmp_save = ft_check_save_argument(argv[2]);
	ft_check_file_path_argument(argv[1]);
	vars->game.file = argv[1];
}

void	ft_validate_input_data(int argc, char **argv, t_vars *vars)
{
	ft_validate_arguments(argc, argv, vars);
	ft_initialize(vars);
	if (ft_scene_description_parameters(vars))
		ft_error(vars->error_message);
	ft_check_parameters(&vars->game);
	ft_check_map(vars);
}
