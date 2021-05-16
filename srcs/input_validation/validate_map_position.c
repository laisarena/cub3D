/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 01:58:13 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 15:50:27 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static void	ft_check_player(char c, int i, int j, t_vars *vars)
{
	if (!ft_is_player(c))
		return ;
	if (vars->player.set)
		ft_error("More then one player position\n");
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

static void	ft_check_sprite(char c, int i, int j, t_vars *vars)
{
	t_sprite	*sprite;

	if (c != '2')
		return ;
	sprite = (t_sprite *)malloc(sizeof(t_sprite));
	sprite->position.x = j;
	sprite->position.y = i;
	ft_lstadd_back(&vars->game.sprites.list, ft_lstnew(sprite));
}

void	ft_check_map(t_vars *vars)
{
	int	i;
	int	j;

	ft_validate_edges(&vars->map);
	i = 0;
	while (i < vars->map.rows)
	{
		j = 0;
		while (j < vars->map.cols)
		{
			ft_check_player(vars->map.matrix[i][j], i, j, vars);
			ft_check_sprite(vars->map.matrix[i][j], i, j, vars);
			j++;
		}
		i++;
	}
	if (!vars->player.set)
		ft_error("No player position\n");
}
