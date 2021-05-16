/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_resolution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 13:12:33 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 13:14:10 by lfrasson         ###   ########.fr       */
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

int	ft_validate_number(char *string, int *parameter)
{
	if (!string || !ft_is_string_number(string))
		return (0);
	*parameter = ft_atoi(string);
	return (1);
}

int	ft_resolution(char **split_line, t_vars *vars)
{
	if (!(ft_validate_number(split_line[1], &vars->game.resolution.width)))
	{
		ft_save_error_message(
			"Misconfiguration on resolution x render size\n", vars);
		return (0);
	}
	if (!(ft_validate_number(split_line[2], &vars->game.resolution.height)))
	{
		ft_save_error_message(
			"Misconfiguration on resolution y render size\n", vars);
		return (0);
	}
	if (split_line[3])
	{
		ft_save_error_message(
			"Misconfiguration on resolution\n", vars);
		return (0);
	}
	vars->game.resolution.identifier = 1;
	vars->game.counter++;
	return (1);
}
