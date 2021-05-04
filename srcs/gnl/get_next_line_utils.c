/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 15:55:52 by lfrasson          #+#    #+#             */
/*   Updated: 2021/04/20 01:23:24 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	break_line_position(char *buffer)
{
	int	position;

	if (!buffer)
		return (-1);
	position = 0;
	while (buffer[position] && position < BUFFER_SIZE)
		if (buffer[position++] == '\n')
			return (position - 1);
	return (-1);
}

char	*bufferlist_to_line(t_list **buffer_list, unsigned int size)
{
	char	*line;
	char	*pointer_line;
	char	*buffer;
	t_list	*tmp;

	if (!*buffer_list)
		return (NULL);
	line = (char *)malloc((size + 1) * sizeof(char));
	if (!line)
		return (NULL);
	pointer_line = line;
	while (*buffer_list)
	{
		tmp = *buffer_list;
		*buffer_list = tmp->next;
		buffer = (char *)tmp->content;
		while (*buffer && size--)
			*line++ = *buffer++;
		free(tmp->content);
		free(tmp);
	}
	free(*buffer_list);
	*line = '\0';
	return (pointer_line);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!content || !node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	ft_lstadd(t_list **list, t_list *node)
{
	t_list	*tmp;

	if (!node || !list)
		return ;
	if (*list == NULL)
		*list = node;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = node;
	}
}
