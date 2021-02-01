/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 16:00:40 by lfrasson          #+#    #+#             */
/*   Updated: 2021/01/31 21:56:30 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	initialize_resolution(t_resolution *resolution)
{
	resolution->identifier = 0;
	resolution->x = 0;
	resolution->y = 0;
}

static	void	initialize_texture(t_texture *texture)
{
	texture->identifier = 0;
	texture->path = NULL;
}

static	void	initialize_color(t_color *color)
{
	color->identifier = 0;
	color->r = 0;
	color->g = 0;
	color->b = 0;
}

void			initialize(t_scene_description *s_scene_description)
{
	s_scene_description->counter = 0;
	initialize_resolution(&s_scene_description->resolution);
	initialize_texture(&s_scene_description->north);
	initialize_texture(&s_scene_description->south);
	initialize_texture(&s_scene_description->west);
	initialize_texture(&s_scene_description->east);
	initialize_texture(&s_scene_description->sprite);
	initialize_color(&s_scene_description->floor);
	initialize_color(&s_scene_description->ceilling);
}
