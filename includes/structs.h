/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 22:03:32 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/12 03:10:26 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

typedef struct s_image_data
{
	void	*image;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_image_data;

typedef struct s_resolution
{
	int	identifier;
	int	width;
	int	height;
}		t_resolution;

typedef struct s_texture
{
	unsigned int	identifier;
	char			*path;
	int				width;
	int				height;
	t_image_data	image;
}					t_texture;

typedef struct s_color
{
	int	identifier;
	int	r;
	int	g;
	int	b;
	int	hex;
}		t_color;

typedef struct s_map
{
	char	**matrix;
	int		rows;
	int		cols;
}			t_map;

typedef struct s_sprites
{
	int			num;
	t_list		*position;
	t_texture	texture;
}				t_sprites;

typedef struct s_game
{
	char			*file;
	unsigned int	counter;
	t_resolution	resolution;
	t_texture		north;
	t_texture		south;
	t_texture		west;
	t_texture		east;
	t_sprites		sprites;
	t_color			floor;
	t_color			ceilling;
}					t_game;

typedef struct s_player
{
	float	x;
	float	y;
	float	width;
	float	height;
	int		turn_direction;
	int		walk_direction;
	float	rotation_angle;
	int		set;
}			t_player;

typedef struct s_ray
{
	float	angle;
	t_coord	wall_hit;
	float	distance;
	int		is_hit_vertical;
	int		is_facing_up;
	int		is_facing_down;
	int		is_facing_left;
	int		is_facing_right;
	int		wall_hit_content;
}			t_ray;

typedef struct s_vars
{	
	t_game			game;
	t_map			map;
	void			*mlx;
	void			*window;
	t_image_data	image;
	t_player		player;
	t_ray			*ray;
	int				bmp_save;
	char			*error_message;
}					t_vars;

typedef struct s_wall
{
	int			height;
	int			top;
	int			bottom;
	t_int_coord	texture_offset;
}				t_wall;

#endif
