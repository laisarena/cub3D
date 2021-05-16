/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 20:35:39 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/16 21:16:10 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_validate_range(int color)
{
	if (color < 0 || color > 255)
		return (0);
	return (1);
}

static int	is_not_null(char *string, t_vars *vars)
{
	if (!string)
		return (0);
	ft_save_error_message("Misconfiguration on color\n", vars);
	return (1);
}

static int	ft_validade_color_number(char **split_color, t_color *color,
		t_vars *vars)
{
	if (split_color && !split_color[3])
	{
		if (ft_validate_number(split_color[0], &color->r)
			&& ft_validate_number(split_color[1], &color->g)
			&& ft_validate_number(split_color[2], &color->b))
		{
			if (ft_validate_range(color->r)
				&& ft_validate_range(color->g)
				&& ft_validate_range(color->b))
			{
				ft_free_split(split_color);
				return (1);
			}
		}
	}
	ft_save_error_message("Misconfiguration on color\n", vars);
	ft_free_split(split_color);
	return (0);
}

static int	ft_rgb_to_hex(int r, int g, int b)
{
	int	hex;

	hex = 0xFF000000;
	hex += r * 0x10000;
	hex += g * 0x100;
	hex += b * 0x1;
	return (hex);
}

int	ft_color(char **split_line, t_vars *vars, t_color *color)
{
	char	**split_color;

	if (is_not_null(split_line[2], vars))
		return (0);
	split_color = ft_split(split_line[1], ',');
	if (!ft_validade_color_number(split_color, color, vars))
		return (0);
	color->hex = ft_rgb_to_hex(color->r, color->g, color->b);
	color->identifier = 1;
	vars->game.counter++;
	return (1);
}
