/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 21:20:42 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 22:06:22 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_VALIDATION_H
# define INPUT_VALIDATION_H

# include "cub3d.h" 

void	ft_validate_input_data(int argc, char **argv, t_vars *vars);
void	ft_validate_arguments(int argc, char **argv, t_vars *vars);
void	ft_initialize(t_vars *vars);
int		ft_scene_description_parameters(t_vars *vars);
int		ft_resolution(char **split_line, t_vars *vars);
int		ft_color(char **split_line, t_vars *vars, t_color *s_color);
int		ft_texture(char **split_line, t_vars *vars, t_texture *s_texture);
void	ft_check_parameters(t_game *game, t_vars *vars);
int		ft_validate_number(char *string, int *parameter);
void	ft_free_split(char **split);
void	ft_create_map_list(int fd, char *line, t_list **map_list, t_vars *vars);
void	ft_check_map(t_vars *vars);
void	ft_validate_edges(t_map *map, t_vars *vars);
void	ft_initialize_resolution(t_resolution *resolution);
void	ft_initialize_texture(t_texture *texture);
void	ft_initialize_color(t_color *color);
void	ft_initialize_map(t_map *map);
void	ft_initialize_sprites(t_sprites *sprites);

#endif
