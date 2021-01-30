/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 15:56:29 by lfrasson          #+#    #+#             */
/*   Updated: 2021/01/30 17:31:26 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

typedef struct
{
	int				bytes_read;
	int				line_size;
	int				position;
}					t_aux;

int					get_next_line(int fd, char **line);
int					break_line_position(char *buffer);
void				ft_lstadd(t_list **list, t_list *node);
t_list				*ft_lstnew(void *content);
char				*bufferlist_to_line(t_list **buffer_list,
										unsigned int size);
#endif
