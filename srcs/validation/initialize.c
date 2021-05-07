/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 16:00:40 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/20 01:19:53 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	ft_initialize_resolution(t_resolution *resolution)
{
	resolution->identifier = 0;
	resolution->x = 0;
	resolution->y = 0;
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

void	ft_initialize(t_vars *vars)
{
	vars->scene_description.counter = 0;
	ft_initialize_resolution(&vars->scene_description.resolution);
	ft_initialize_texture(&vars->scene_description.north);
	ft_initialize_texture(&vars->scene_description.south);
	ft_initialize_texture(&vars->scene_description.west);
	ft_initialize_texture(&vars->scene_description.east);
	ft_initialize_texture(&vars->scene_description.sprite);
	ft_initialize_color(&vars->scene_description.floor);
	ft_initialize_color(&vars->scene_description.ceilling);
	ft_initialize_map(&vars->map);
}