/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 16:00:40 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 13:43:35 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_initialize_resolution(t_resolution *resolution)
{
	resolution->identifier = 0;
	resolution->width = 0;
	resolution->height = 0;
}

void	ft_initialize_texture(t_texture *texture)
{
	texture->identifier = 0;
	texture->path = NULL;
}

void	ft_initialize_color(t_color *color)
{
	color->identifier = 0;
	color->r = 0;
	color->g = 0;
	color->b = 0;
}

void	ft_initialize_map(t_map *map)
{
	map->rows = 0;
	map->cols = 0;
	map->matrix = NULL;
}

void	ft_initialize_sprites(t_sprites *sprites)
{
	sprites->num = 0;
	sprites->list = NULL;
	sprites->list_visible = NULL;
	ft_initialize_texture(&sprites->texture);
}
