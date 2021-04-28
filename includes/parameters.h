/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 22:03:32 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/28 20:31:02 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMETERS_H
# define PARAMETERS_H

#include "cub3d.h"

typedef struct
{
	int	identifier;
	int	x;
	int	y;
}		t_resolution;

typedef struct
{
	unsigned int	identifier;
	char			*path;
}					t_texture;

typedef struct
{
	int	identifier;
	int	r;
	int	g;
	int	b;
}		t_color;

typedef struct
{
	char	**matrix;
	int		rows;
	int		cols;
}			t_map;

typedef struct
{
	char			*file;
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

typedef struct
{
	void			*image;
	char			*address;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_image_data;

typedef struct
{
	float			x;
	float			y;
	float			width;
	float			height;
	int				turn_direction;
	int				walk_direction;
	float			rotation_angle;
	float			walk_speed;
	float			turn_speed;
}					t_player;

typedef struct
{
	float			angle;
	t_coordinate	wall_hit;
	float			distance;
	int				is_hit_vertical;
	int				is_facing_up;
	int				is_facing_down;
	int				is_facing_left;
	int				is_facing_right;
	int				wall_hit_content;
}					t_ray;

typedef struct
{	
	t_scene_description	scene_description;
	t_map				map;
	void				*mlx;
	void				*window;
	t_image_data		image;
	t_player			player;
	t_ray				*ray;
	char				*message;
}						t_vars;

#endif
