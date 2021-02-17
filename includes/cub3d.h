/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:37:23 by lfrasson          #+#    #+#             */
/*   Updated: 2021/02/03 22:24:11 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "get_next_line.h"
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>

typedef struct
{
	unsigned int	identifier;
	unsigned int	x;
	unsigned int	y;
}					t_resolution;

typedef struct
{
	unsigned int	identifier;
	char			*path;
}					t_texture;

typedef struct
{
	unsigned int	identifier;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}					t_color;

typedef struct
{
	unsigned int	counter;
	t_resolution	resolution;
	t_texture		north;
	t_texture		south;
	t_texture		west;
	t_texture		east;
	t_texture		sprite;
	t_color			floor;
	t_color			ceilling;
}					t_scene_description;

void				ft_validate_arguments(int argc, char **argv);
void				ft_error(char *message);
void				ft_initialize(t_scene_description *s_scene_description);
void				ft_scene_description_parameters(
						char *scene_description_file,
						t_scene_description *s_scene_description);
#endif
