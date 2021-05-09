/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:44 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/09 23:14:46 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_free_map(t_vars *vars)
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

static void	ft_free_texture(t_vars *vars)
{
	free(vars->game.north.path);
	free(vars->game.south.path);
	free(vars->game.west.path);
	free(vars->game.east.path);
}

void	ft_free_resources(t_vars *vars)
{
	ft_free_map(vars);
	ft_free_texture(vars);
	free(vars->ray);
}

int	ft_close(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->image.image);
	mlx_destroy_image(vars->mlx, vars->game.north.image.image);
	mlx_destroy_image(vars->mlx, vars->game.south.image.image);
	mlx_destroy_image(vars->mlx, vars->game.west.image.image);
	mlx_destroy_image(vars->mlx, vars->game.east.image.image);
	if (vars->window)
		mlx_destroy_window(vars->mlx, vars->window);
	free(vars->mlx);
	ft_free_resources(vars);
	exit(0);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i++] = NULL;
	}
	free(split);
	split = NULL;
}
