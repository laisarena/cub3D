/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 01:58:13 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/08 03:08:41 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_is_player_position(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static void	ft_save_position(char c, int i, int j, t_vars *vars)
{
	if (vars->player.set)
		ft_error("More then one player position");
	vars->player.set++;
	vars->player.x = j;
	vars->player.y = i;
	if (c == 'N')
		vars->player.rotation_angle = 1.5 * PI;
	else if (c == 'S')
		vars->player.rotation_angle = 0.5 * PI;
	else if (c == 'E')
		vars->player.rotation_angle = 0;
	else if (c == 'W')
		vars->player.rotation_angle = PI;
}

void	ft_check_map(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while(i < vars->map.rows)
	{
		j = 0;
		while( j < vars->map.cols)
		{
			if (ft_is_player_position(vars->map.matrix[i][j]))
				ft_save_position(vars->map.matrix[i][j], i, j, vars);
			j++;
		}
		i++;
	}
	if (!vars->player.set)
		ft_error("No player position");
}
