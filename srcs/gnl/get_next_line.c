/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 15:54:38 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/20 01:27:40 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Description
**		Function which returns a line read from a file descriptor,
**		without the newline.
** Parameters
**		fd		- file descriptor for reading
**		**line	- The value of what has been read
** Return
**		1 : A line has been read
**		0 : EOF has been reached
**		-1 : An error happened
*/

static int	ft_move_rest(char *dst, char *src)
{
	int	i;
	int	size;

	if (!src || !dst)
		return (-1);
	i = 0;
	while (*src && i++ < BUFFER_SIZE)
		*dst++ = *src++;
	size = i;
	while (i++ < BUFFER_SIZE)
		*dst++ = '\0';
	return (size);
}

static void	save_rest(int position, char *buffer, char *rest)
{
	if (position == -1)
		return ;
	ft_move_rest(rest, buffer + position + 1);
	buffer[position] = '\0';
}

static t_list	*take_from_file(int fd, char **rest,
								t_list *buffer_list, t_aux *aux)
{
	char	*buffer;

	while (aux->position == -1 && aux->bytes_read)
	{
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (NULL);
		aux->bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[aux->bytes_read] = '\0';
		aux->line_size += aux->bytes_read;
		aux->position = break_line_position(buffer);
		save_rest(aux->position, buffer, *rest);
		ft_lstadd(&buffer_list, ft_lstnew(buffer));
	}
	return (buffer_list);
}

static t_list	*analize_rest(char **rest, t_list *buffer_list, t_aux *aux)
{
	char	*buffer;

	if (!*rest)
		*rest = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	else
	{
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (NULL);
		aux->line_size = ft_move_rest(buffer, *rest);
		aux->position = break_line_position(buffer);
		save_rest(aux->position, buffer, *rest);
		ft_lstadd(&buffer_list, ft_lstnew(buffer));
	}
	return (buffer_list);
}

int	get_next_line(int fd, char **line)
{
	static char	*rest[_SC_OPEN_MAX];
	t_list		*buffer_list;
	t_aux		aux;

	if (fd < 0 || BUFFER_SIZE < 1 || !line || read(fd, NULL, 0))
		return (-1);
	buffer_list = NULL;
	aux.line_size = 0;
	aux.bytes_read = -2;
	aux.position = -1;
	buffer_list = analize_rest(&rest[fd], buffer_list, &aux);
	buffer_list = take_from_file(fd, &rest[fd], buffer_list, &aux);
	*line = bufferlist_to_line(&buffer_list, aux.line_size);
	if (aux.bytes_read == 0)
	{
		free(rest[fd]);
		rest[fd] = NULL;
		return (0);
	}
	return (1);
}
