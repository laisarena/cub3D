/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 21:20:42 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/05 20:16:41 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# include "cub3d.h" 

void	ft_validate_arguments(int argc, char **argv, t_vars *vars);
void	ft_initialize(t_vars *vars);
int		ft_scene_description_parameters(t_vars *vars);
int		ft_color(char **split_line, t_vars *vars, t_color *s_color);
void	ft_check_parameters(t_scene_description *s_scene_description);
int		ft_validate_number(char *string, int *parameter);
void	ft_free_split(char **split);

#endif
