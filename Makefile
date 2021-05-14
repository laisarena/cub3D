#
#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfrasson <lfrasson@student.42sp.org.b      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/19 14:07:28 by lfrasson          #+#    #+#              #
#    Updated: 2021/05/07 02:02:28 by lfrasson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFT = libft.a

PATH_INCLUDE = ./includes/

PATH_LIBFT = ./libft/

PATH_MLX = ./minilibx-linux/

PATH_SRCS = ./srcs/

SRCS = main.c\
	   error_handler.c\
	   free_resources.c\
	   input_validation/validate_arguments.c\
	   input_validation/validate_input_data.c\
	   input_validation/initialize.c\
	   input_validation/validate_scene_description.c\
	   input_validation/validate_color.c\
	   input_validation/validate_texture.c\
	   input_validation/validate_map.c\
	   input_validation/validate_map_2.c\
	   game/game.c\
	   game/setup.c\
	   game/minimap.c\
	   game/player_movements.c\
	   game/rays.c\
	   game/render_rays.c\
	   game/projection.c\
	   game/draw.c\
	   game/draw_line.c\
	   game/texture.c\
	   game/sprites.c\
	   game/utils.c\
	   gnl/get_next_line.c\
	   gnl/get_next_line_utils.c\
	   bitmap/bitmap.c\

OBJS = $(addprefix $(PATH_SRCS),$(SRCS:.c=.o))

#FLAGS = -Wall -Wextra
FLAGS = -Wall -Wextra -Werror
FLAGS_MLX = -lm -lX11 -lXext

.c.o:
	gcc -g $(FLAGS) -I$(PATH_INCLUDE) -I$(PATH_LIBFT) -I$(PATH_MLX) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	make bonus -C $(PATH_LIBFT)
	make -C $(PATH_MLX)
	#gcc  -g -fsanitize=address $(FLAGS) $(OBJS) -L$(PATH_LIBFT) -lft -I$(PATH_LIBFT) -L$(PATH_MLX) -lmlx -I$(PATH_MLX) $(FLAGS_MLX) -o $(NAME)
	gcc  -g  $(FLAGS) $(OBJS) -L$(PATH_LIBFT) -lft -I$(PATH_LIBFT) -L$(PATH_MLX) -lmlx -I$(PATH_MLX) $(FLAGS_MLX) -o $(NAME)
	#gcc $(FLAGS) $(OBJS) -L$(PATH_LIBFT) -lft -I$(PATH_LIBFT) -L$(PATH_MLX) -lmlx -I$(PATH_MLX) $(FLAGS_MLX) -o $(NAME)

all:	$(NAME)

clean:
	make clean -C $(PATH_LIBFT)
	make clean -C $(PATH_MLX)
	rm -f $(OBJS)
	rm *.bmp

fclean: clean
	make fclean -C $(PATH_LIBFT)
	rm -f $(NAME)

re: fclean all

sani: $(NAME)
	gcc  -g -fsanitize=address $(FLAGS) $(OBJS) -L$(PATH_LIBFT) -lft -I$(PATH_LIBFT) -L$(PATH_MLX) -lmlx -I$(PATH_MLX) $(FLAGS_MLX) -o $(NAME)

.PHONY: all clean fclean re

