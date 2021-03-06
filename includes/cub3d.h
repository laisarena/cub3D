/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:37:23 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 21:51:12 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../srcs/gnl/get_next_line.h"
# include "auxiliary_structs.h"
# include "structs.h"
# include "constants.h"
# include "input_validation.h"
# include "map.h"
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

void	ft_error(char *message, t_vars *vars);
void	ft_save_error_message(char *message, t_vars *vars);
void	ft_free_resources(t_vars *vars);
void	ft_free_null(void *pointer);
void	ft_exit(int fd, char *line, t_list **map_list, t_vars *vars);
void	ft_del(void *pointer);
void	ft_game(t_vars *vars);
void	ft_setup(t_vars *vars);
int		ft_loop(t_vars *vars);
void	ft_draw_line(t_vars *vars, t_int_coord p0, t_int_coord p1, int color);
void	ft_put_pixel(t_image_data *image, int x, int y, int color);
void	ft_rectangle_on_image(t_vars *vars, t_retangle retangle, int color);
void	ft_render_minimap_grid(t_vars *vars);
void	ft_clean_direction_moviments(t_player *player);
void	ft_move_player(t_vars *vars);
void	ft_render_minimap_player(t_vars *vars);
void	ft_render_minimap_sprites(t_vars *vars);
void	ft_cast_rays(t_vars *vars);
void	ft_render_minimap_rays(t_vars *vars);
int		ft_is_wall_at(float x, float y, t_vars *vars);
void	ft_render(t_vars *vars);
void	ft_render_projection(t_vars *vars);
void	ft_render_sprites_projection(t_vars *vars);
int		ft_close(t_vars *vars);
void	ft_define_visible_sprites(t_vars *vars);
int		ft_key_press(int keycode, t_vars *vars);
int		ft_calc_x_texture_offset(t_ray ray, t_texture *texture);
int		ft_calc_y_texture_offset(t_wall wall, int y, int win_height);
void	ft_create_texture_images(t_vars *vars);
float	ft_distance_between_points(float x1, float y1, float x2, float y2);
float	ft_normalize_angle(float angle);
void	ft_render_floor(t_wall wall, t_vars *vars, int x);
void	ft_render_ceiling(t_wall wall, t_vars *vars, int x);
float	ft_calc_top(int win_hight, int height);
float	ft_calc_bottom(int win_height, int height);
int		ft_get_color(t_image_data *image, int x, int y);
void	ft_free_list(t_list **lst);
int		ft_write_bmp_file(t_vars *vars);
void	ft_clear_image(t_vars *vars);
void	ft_save_bmp_file(t_vars *vars);
void	ft_create_window(t_vars *vars);
void	ft_initialize_sprites_position(t_list *sprite_list);

#endif
