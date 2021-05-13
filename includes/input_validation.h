/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 21:20:42 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/09 20:11:36 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_VALIDATION_H
# define INPUT_VALIDATION_H

# include "cub3d.h" 

void	ft_validate_input_data(int argc, char **argv, t_vars *vars);
void	ft_validate_arguments(int argc, char **argv, t_vars *vars);
void	ft_initialize(t_vars *vars);
int		ft_scene_description_parameters(t_vars *vars);
int		ft_color(char **split_line, t_vars *vars, t_color *s_color);
int		ft_texture(char **split_line, t_vars *vars, t_texture *s_texture);
void	ft_check_parameters(t_game *s_scene_description);
int		ft_validate_number(char *string, int *parameter);
void	ft_free_split(char **split);
void	ft_check_map(t_vars *vars);

#endif