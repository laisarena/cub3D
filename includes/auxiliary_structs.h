/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 23:38:57 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/23 02:56:02 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUXILIARY_STRUCTS_H
# define AUXILIARY_STRUCTS_H

typedef struct
{
	float	x;
	float	y;
}			t_coordinate;

typedef struct
{
	t_coordinate	intercept;
	t_coordinate	step;
	t_coordinate	next_touch;
	t_coordinate	wall_hit;
	int				found_wall_hit;
	int				wall_content;
}					t_intersection;

#endif
