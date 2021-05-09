/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 23:09:22 by lfrasson          #+#    #+#             */
/*   Updated: 2021/05/07 21:01:47 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_not_null(char *string, t_vars *vars)
{
	if (!string)
		return (0);
	ft_save_error_message("Misconfiguration on texture\n", vars);
	return (1);
}

static int	ft_open_texture_file(char *file, t_vars *vars)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd > -1)
		return (fd);
	ft_save_error_message(NULL, vars);
	return (0);
}

static char	*ft_save_path(char *str)
{
	char	*dst;
	int		len;

	len = ft_strlen(str);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	ft_strlcpy(dst, str, len + 1);
	return (dst);
}

int	ft_texture(char **split_line, t_vars *vars, t_texture *texture)
{
	int	fd;

	if (is_not_null(split_line[2], vars))
		return (0);
	fd = ft_open_texture_file(split_line[1], vars);
	close(fd);
	texture->path = ft_save_path(split_line[1]);
	texture->identifier = 1;
	vars->game.counter++;
	return (1);
}
