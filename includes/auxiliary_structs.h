/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 23:38:57 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/29 01:30:45 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUXILIARY_STRUCTS_H
# define AUXILIARY_STRUCTS_H

typedef struct s_coordinate
{
	float	x;
	float	y;
}			t_coordinate;

typedef struct s_int_coordinate
{
	int	x;
	int	y;
}		t_int_coordinate;

typedef struct s_retangle
{
	t_coordinate	position;
	int				width;
	int				height;
}					t_retangle;

typedef struct s_intersection
{
	t_coordinate	intercept;
	t_coordinate	step;
	t_coordinate	next_touch;
	t_coordinate	wall_hit;
	int				found_wall_hit;
	int				hit_distance;
	int				wall_content;
}					t_intersection;

#endif
