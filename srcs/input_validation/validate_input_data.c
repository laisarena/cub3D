/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 23:17:23 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/12 01:56:26 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_validate_input_data(int argc, char **argv, t_vars *vars)
{
	ft_validate_arguments(argc, argv, vars);
	ft_initialize(vars);
	if (ft_scene_description_parameters(vars))
		ft_error(vars->error_message);
	ft_check_parameters(&vars->game);
	ft_check_map(vars);
}
