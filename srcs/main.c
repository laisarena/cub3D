/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:44 by lfrasson          #+#    #+#             */
/*   Updated: 2021/03/17 23:14:28 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_save_error_message(char *message, t_vars *vars)
{
	vars->message = message;
}

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
	t_vars vars;

	errno = 0;
	vars.message = NULL;
	ft_validate_arguments(argc, argv);
	ft_initialize(&vars.scene_description);
	vars.scene_description.file = argv[1];
	if (!(ft_scene_description_parameters(&vars)))
		ft_error(vars.message);
	ft_check_parameters(&vars.scene_description);
	ft_minilibx(&vars);
	return (0);
}
