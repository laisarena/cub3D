/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:37:23 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/09 01:57:30 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"
# include "parameters.h"
# include "map.h"
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

void	ft_validate_arguments(int argc, char **argv);
void	ft_error(char *message);
void	ft_save_error_message(char *message, t_vars *vars);
void	ft_initialize(t_scene_description *s_scene_description);
int		ft_scene_description_parameters(t_vars *vars);
void	ft_minilibx(t_vars *vars);
void	ft_check_parameters(t_scene_description *s_scene_description);
void	ft_free_map(t_vars *vars);
void	draw_line(t_vars *vars, int x0, int y0, int x1, int y1, int color);
void	ft_put_pixel(t_image_data *image, int x, int y, int color);

#endif
