/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:44 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 21:47:32 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_save_error_message(char *message, t_vars *vars)
{
	vars->error_message = message;
}

void	ft_error(char *message, t_vars *vars)
{
	int	errnum;

	errnum = errno;
	ft_putstr_fd("Error\n", 1);
	if (!errnum)
		ft_putstr_fd(message, 1);
	else
		printf("%s\n", strerror(errnum));
	ft_free_resources(vars);
	exit(-1);
}
