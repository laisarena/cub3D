/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 16:00:40 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/12 02:11:47 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	ft_initialize_resolution(t_resolution *resolution)
{
	resolution->identifier = 0;
	resolution->width = 0;
	resolution->height = 0;
}

static	void	ft_initialize_texture(t_texture *texture)
{
	texture->identifier = 0;
	texture->path = NULL;
}

static	void	ft_initialize_color(t_color *color)
{
	color->identifier = 0;
	color->r = 0;
	color->g = 0;
	color->b = 0;
}

static	void	ft_initialize_map(t_map *map)
{
	map->rows = 0;
	map->cols = 0;
	map->matrix = NULL;
}

static	void	ft_initialize_sprites(t_sprites *sprites)
{
	sprites->num = 0;
	sprites->position = NULL;
	ft_initialize_texture(&sprites->texture);
}

void	ft_initialize(t_vars *vars)
{
	vars->game.counter = 0;
	ft_initialize_resolution(&vars->game.resolution);
	ft_initialize_texture(&vars->game.north);
	ft_initialize_texture(&vars->game.south);
	ft_initialize_texture(&vars->game.west);
	ft_initialize_texture(&vars->game.east);
	ft_initialize_sprites(&vars->game.sprites);
	ft_initialize_color(&vars->game.floor);
	ft_initialize_color(&vars->game.ceilling);
	ft_initialize_map(&vars->map);
	vars->player.set = 0;
}
