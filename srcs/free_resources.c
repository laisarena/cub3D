/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:03:44 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 22:10:37 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_free_map(t_vars *vars)
{
	int	i;

	i = 0;
	if (!vars->map.matrix)
		return ;
	while (vars->map.matrix[i])
		ft_free_null(vars->map.matrix[i++]);
	ft_free_null(vars->map.matrix);
}

static void	ft_free_texture(t_vars *vars)
{
	ft_free_null(vars->game.north.path);
	ft_free_null(vars->game.south.path);
	ft_free_null(vars->game.west.path);
	ft_free_null(vars->game.east.path);
	ft_free_null(vars->game.sprites.texture.path);
}

void	ft_free_resources(t_vars *vars)
{
	ft_free_map(vars);
	ft_free_texture(vars);
	ft_lstclear(&vars->game.sprites.list, &ft_del);
	ft_lstclear(&vars->game.sprites.list_visible, &ft_del);
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
