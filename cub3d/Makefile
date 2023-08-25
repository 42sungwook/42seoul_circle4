# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seulee2 <seulee2@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/25 12:24:58 by seulee2           #+#    #+#              #
#    Updated: 2023/08/25 15:43:46 by seulee2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 		./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c \
				./draw/draw_player.c ./draw/draw_fov.c ./draw/draw.c \
				./init/check_space.c ./init/free_functions.c ./init/init_game.c ./init/init_img.c ./init/init_map.c ./init/set_color.c \
				./raycasting/calculation_utils.c ./raycasting/cast_rays.c ./raycasting/shoot_ray.c \
				./srcs/handle_keys.c ./srcs/main.c \
				./valid/check_map.c

SRCS_B =	./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c \
				./draw/draw_minimap_bonus.c ./draw/draw_player_bonus.c ./draw/draw_fov_bonus.c ./draw/draw_bonus.c \
				./init/check_space_bonus.c ./init/free_functions_bonus.c ./init/init_game_bonus.c ./init/init_img_bonus.c ./init/init_map_bonus.c ./init/set_color_bonus.c \
				./raycasting/calculation_utils_bonus.c ./raycasting/cast_rays_bonus.c ./raycasting/shoot_ray_bonus.c \
				./srcs/handle_keys_bonus.c ./srcs/main_bonus.c \
				./valid/check_map_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

NAME = cub3D

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
MLXLIB	=	-lm -Lmlx -lmlx -framework OpenGL -framework Appkit -Imlx
LFLAGS	=	-lft -Llibft
LIBFT	=	libft/libft.a
MLX		=	mlx/libmlx.a

ifdef BONUS
 	OBJS_ALL = $(OBJS_B)
else
	OBJS_ALL = $(OBJS)
endif

all:	$(NAME)

$(NAME):	$(OBJS_ALL) $(LIBFT) $(MLX)
			$(CC) $(CFLAGS) $(MLXLIB) $(LFLAGS) $(OBJS_ALL) -o $(NAME)

$(LIBFT):
			make -C libft

$(MLX):
			make -C mlx

%.o : %.c
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			rm -rf $(OBJS) $(OBJS_B)
			make -C libft clean
			make -C mlx clean

fclean:		clean
			rm -rf $(NAME)
			rm -rf $(LIBFT)
			rm -rf $(MLX)

re:			fclean
			make all

bonus:
	make BONUS=1 all

.PHONY:		all clean fclean re bonus
