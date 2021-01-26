# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfrasson <lfrasson@student.42sp.org.b      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/19 14:07:28 by lfrasson          #+#    #+#              #
#    Updated: 2021/01/21 19:46:44 by lfrasson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFT = libft.a

PATH_INCLUDE = ./includes/

PATH_LIBFT = ./libft/

PATH_SRCS = ./srcs/

SRCS = main.c\

OBJS = $(addprefix $(PATH_SRCS),$(SRCS:.c=.o))

FLAGS = -Wall -Wextra -Werror

.c.o:
	gcc $(FLAGS) -I$(PATH_INCLUDE) -I$(PATH_LIBFT) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	make -C $(PATH_LIBFT)
	gcc $(FLAGC) $(OBJS) -L$(PATH_LIBFT) -lft -I$(PATH_LIBFT) -o $(NAME)

all:	$(NAME)

clean:
	make clean -C $(PATH_LIBFT)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(PATH_LIBFT)
	rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re

