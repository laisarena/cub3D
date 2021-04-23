/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:44 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/23 02:56:33 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_map(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->map.matrix[i])
	{
		free(vars->map.matrix[i]);
		vars->map.matrix[i] = NULL;
		i++;
	}
	free(vars->map.matrix);
	vars->map.matrix = NULL;
}

void	ft_save_error_message(char *message, t_vars *vars)
{
	vars->message = message;
}

void	ft_error(char *message)
{
	int	errnum;

	errnum = errno;
	ft_putstr_fd("Error\n", 1);
	if (!errnum)
		ft_putstr_fd(message, 1);
	else
		printf("%s\n", strerror(errnum));
	exit(-1);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	errno = 0;
	vars.message = NULL;
	ft_validate_arguments(argc, argv);
	ft_initialize(&vars);
	vars.scene_description.file = argv[1];
	if (ft_scene_description_parameters(&vars))
		ft_error(vars.message);
	ft_check_parameters(&vars.scene_description);
	ft_minilibx(&vars);
	ft_free_map(&vars);
	free(vars.ray);
	return (0);
}
