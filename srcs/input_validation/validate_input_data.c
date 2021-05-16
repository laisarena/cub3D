/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 23:17:23 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 13:21:27 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_parameters(t_game *game)
{
	if (game->resolution.identifier == 0)
		ft_error("Missing R parameter\n");
	if (game->north.identifier == 0)
		ft_error("Missing NO parameter\n");
	if (game->south.identifier == 0)
		ft_error("Missing SO Parameter\n");
	if (game->west.identifier == 0)
		ft_error("Missing WE parameter\n");
	if (game->east.identifier == 0)
		ft_error("Missing EA parameter\n");
	if (game->sprites.texture.identifier == 0)
		ft_error("Missing S parameter\n");
	if (game->floor.identifier == 0)
		ft_error("Missing F parameter\n");
	if (game->ceilling.identifier == 0)
		ft_error("Missing C parameter\n");
}

void	ft_initialize(t_vars *vars)
{
	ft_initialize_resolution(&vars->game.resolution);
	ft_initialize_texture(&vars->game.north);
	ft_initialize_texture(&vars->game.south);
	ft_initialize_texture(&vars->game.west);
	ft_initialize_texture(&vars->game.east);
	ft_initialize_sprites(&vars->game.sprites);
	ft_initialize_color(&vars->game.floor);
	ft_initialize_color(&vars->game.ceilling);
	ft_initialize_map(&vars->map);
	vars->game.counter = 0;
	vars->player.set = 0;
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
