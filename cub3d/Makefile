SRCS = ./libft/ft_atoi.c ./libft/ft_bzero.c ./libft/ft_isalnum.c ./libft/ft_isalpha.c ./libft/ft_isascii.c \
				./libft/ft_isdigit.c ./libft/ft_isprint.c ./libft/ft_itoa.c ./libft/ft_memchr.c ./libft/ft_memcmp.c \
				./libft/ft_memcpy.c ./libft/ft_memmove.c ./libft/ft_memset.c ./libft/ft_putchar_fd.c ./libft/ft_putendl_fd.c \
				./libft/ft_putnbr_fd.c ./libft/ft_putstr_fd.c ./libft/ft_split.c ./libft/ft_strchr.c ./libft/ft_striteri.c \
				./libft/ft_strjoin.c ./libft/ft_strlcat.c ./libft/ft_strlcpy.c ./libft/ft_strlen.c ./libft/ft_strmapi.c \
				./libft/ft_strncmp.c ./libft/ft_strnstr.c ./libft/ft_strrchr.c ./libft/ft_strtrim.c ./libft/ft_substr.c \
				./libft/ft_tolower.c ./libft/ft_toupper.c ./libft/ft_calloc.c ./libft/ft_strdup.c \
				./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c \
				./draw/draw_player.c ./draw/draw_fov.c ./draw/draw.c \
				./init/check_space.c ./init/free_functions.c ./init/init_game.c ./init/init_img.c ./init/init_map.c ./init/set_color.c \
				./raycasting/calculation_utils.c ./raycasting/cast_rays.c ./raycasting/shoot_ray.c \
				./srcs/handle_keys.c ./srcs/main.c \
				./valid/check_map.c

SRCS_B = ./libft/ft_atoi.c ./libft/ft_bzero.c ./libft/ft_isalnum.c ./libft/ft_isalpha.c ./libft/ft_isascii.c \
				./libft/ft_isdigit.c ./libft/ft_isprint.c ./libft/ft_itoa.c ./libft/ft_memchr.c ./libft/ft_memcmp.c \
				./libft/ft_memcpy.c ./libft/ft_memmove.c ./libft/ft_memset.c ./libft/ft_putchar_fd.c ./libft/ft_putendl_fd.c \
				./libft/ft_putnbr_fd.c ./libft/ft_putstr_fd.c ./libft/ft_split.c ./libft/ft_strchr.c ./libft/ft_striteri.c \
				./libft/ft_strjoin.c ./libft/ft_strlcat.c ./libft/ft_strlcpy.c ./libft/ft_strlen.c ./libft/ft_strmapi.c \
				./libft/ft_strncmp.c ./libft/ft_strnstr.c ./libft/ft_strrchr.c ./libft/ft_strtrim.c ./libft/ft_substr.c \
				./libft/ft_tolower.c ./libft/ft_toupper.c ./libft/ft_calloc.c ./libft/ft_strdup.c \
				./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c \
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

ifdef BONUS
 	OBJS_ALL = $(OBJS_B)
else
	OBJS_ALL = $(OBJS)
endif

ifdef DEBUG
	CFLAGS += -g3 -fsanitize=address
endif

all:	$(NAME)

$(NAME):	$(OBJS_ALL)
			$(CC) $(CFLAGS) $(MLXLIB) $(OBJS_ALL) -o $(NAME)

%.o : %.c
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			rm -rf $(OBJS) $(OBJS_B)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

bonus:
	make BONUS=1 all

.PHONY:		all clean fclean re bonus