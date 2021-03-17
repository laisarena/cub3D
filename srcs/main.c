/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:44 by lfrasson          #+#    #+#             */
/*   Updated: 2021/03/16 02:15:04 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_error(char *message)
{
	int		errnum;

	errnum = errno;
	ft_putstr_fd("Error\n", 1);
	if (!errnum)
		ft_putstr_fd(message, 1);
	else
		printf("%s\n", strerror(errnum));
	exit(-1);
}

int			main(int argc, char **argv)
{
	t_scene_description	scene_description;

	(void)argc;
	(void)argv;
	errno = 0;
	ft_validate_arguments(argc, argv);
	ft_initialize(&scene_description);
	scene_description.file = argv[1];
	ft_scene_description_parameters(&scene_description);
	ft_check_parameters(&scene_description);
	ft_minilibx(&scene_description);
	return (0);
}
