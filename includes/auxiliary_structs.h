/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 23:38:57 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/09 20:59:46 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUXILIARY_STRUCTS_H
# define AUXILIARY_STRUCTS_H

typedef struct s_coord
{
	float	x;
	float	y;
}			t_coord;

typedef struct s_int_coord
{
	int	x;
	int	y;
}		t_int_coord;

typedef struct s_retangle
{
	t_coord	position;
	int		width;
	int		height;
}			t_retangle;

typedef struct s_intersection
{
	t_coord	intercept;
	t_coord	step;
	t_coord	next_touch;
	t_coord	wall_hit;
	int		found_wall_hit;
	int		hit_distance;
	int		wall_content;
}			t_intersection;

#endif
