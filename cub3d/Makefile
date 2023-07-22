# **************************************************************************** #
# ProgramName && Files                                                         #
# **************************************************************************** #
NAME		=	cub3D
INC_FILES	=	cub3d.h
SRC_FILES	=	main.c parsing.c
INIT_FILES	=	init_base.c init_img.c
GNL_FILES	=	get_next_line.c get_next_line_utils.c
LIBFT_FILES	=	ft_atoi.c \
				ft_bzero.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_calloc.c \
				ft_strdup.c

# **************************************************************************** #
# Directories && Paths                                                         #
# **************************************************************************** #
INC_DIR		=	./
SRC_DIR		=	./
INIT_DIR	=	./init/
GNL_DIR		=	./get_next_line/
LIBFT_DIR	=	./libft/
OBJ_DIR		=	.obj/
DEP_DIR		=	.dep/
SRCS		=	$(addprefix $(LIBFT_DIR), $(LIBFT_FILES)) $(addprefix $(GNL_DIR), $(GNL_FILES)) \
				$(addprefix $(INIT_DIR), $(INIT_FILES)) $(addprefix $(SRC_DIR), $(SRC_FILES)) 
OBJS		=	$(LIBFT_FILES:%.c=$(OBJ_DIR)%.o) $(GNL_FILES:%.c=$(OBJ_DIR)%.o) \
				$(INIT_FILES:%.c=$(OBJ_DIR)%.o) $(SRC_FILES:%.c=$(OBJ_DIR)%.o)
DEPS		=	$(LIBFT_FILES:%.c=$(DEP_DIR)%.d) $(GNL_FILES:%.c=$(DEP_DIR)%.o) \
				$(INIT_FILES:%.c=$(DEP_DIR)%.d) $(SRC_FILES:%.c=$(DEP_DIR)%.d)
# **************************************************************************** #
# Compiler && flags                                                            #
# **************************************************************************** #
CXX			=	cc
CXXFLAGS	=
MLXFLAGS	=	-L./mlx -lmlx -framework OpenGL -framework AppKit
CPPFLAGS	=	-I$(INC_DIR)
DEPFLAGS	=	-MMD -MP -MF $(@:$(OBJ_DIR)%.o=$(DEP_DIR)%.d)
RM			=	rm -rf
# **************************************************************************** #
# Debug options                                                                #
# **************************************************************************** #
ifdef DEBUG
	CXXFLAGS += -pedantic -g -fsanitize=address,undefined
endif
ifdef C
	CXX = c++-7
endif
Q = @
ifdef PRINT
	Q =
endif
# **************************************************************************** #
# Output controls                                                              #
# **************************************************************************** #
NAME_LEN = $(shell echo $(NAME) | tr -d '\n' | wc -c)
ifeq ($(shell echo "$(NAME_LEN)-6" | bc | grep -c '-'), 1)
	N = 10
else
	N = $(NAME_LEN)
endif
RST =	\033[0m
GRN =	\033[1;32m
CYN =	\033[1;36m
BCY =	\033[1;96m
HOM =	\033[A
CLR =	\033[K
# **************************************************************************** #
# Rules                                                                        #
# **************************************************************************** #
.DEFAULT_GOAL   =   all
-include $(DEPS)
all				:	$(NAME)
src_message:
	@printf "$(CLR)$(GRN)%$Ns is Ready ✅\\n$(RST)" SRC_FILE
init_message:
	@printf "$(CLR)$(GRN)%$Ns is Ready ✅\\n$(RST)" INIT_FILE
gnl_message:
	@printf "$(CLR)$(GRN)%$Ns is Ready ✅\\n$(RST)" GNL_FILE
libft_message:
	@printf "$(CLR)$(GRN)%$Ns is Ready ✅\\n$(RST)" LIBFT_FILE

$(NAME)			:	$(OBJS)
					$Q$(CXX) $(CXXFLAGS) $(MLXFLAGS) -o $@ $(OBJS)
					@printf "$(CLR)$(GRN)%$Ns is Ready ✅\\n$(RST)" $(NAME)
$(OBJ_DIR)%.o	:	$(LIBFT_DIR)%.c 
					@mkdir -p $(OBJ_DIR) $(DEP_DIR)
					@printf "$(CLR)$(GRN)%$Ns is Ready : $<$(RST)$(HOM)\\n" $(NAME)
					$Q$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<
$(OBJ_DIR)%.o	:	$(GNL_DIR)%.c libft_message
					@mkdir -p $(OBJ_DIR) $(DEP_DIR)
					@printf "$(CLR)$(GRN)%$Ns is Ready : $<$(RST)$(HOM)\\n" $(NAME)
					$Q$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<
$(OBJ_DIR)%.o	:	$(INIT_DIR)%.c gnl_message
					@mkdir -p $(OBJ_DIR) $(DEP_DIR)
					@printf "$(CLR)$(GRN)%$Ns is Ready : $<$(RST)$(HOM)\\n" $(NAME)
					$Q$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<
$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c init_message
					@mkdir -p $(OBJ_DIR) $(DEP_DIR)
					@printf "$(CLR)$(GRN)%$Ns is Ready : $<$(RST)$(HOM)\\n" $(NAME)
					$Q$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<
clean			:
					$Q$(RM) $(OBJ_DIR) $(DEP_DIR) *.dSYM
					@printf "$(CYN)%$Ns Objects! 🗑$(RST)\\n" Remove
fclean			:   clean
					$Q$(RM) $(NAME)
					@printf "$(BCY)%$Ns Program! 🗑$(RST)\\n" Remove
re				:	fclean
					@make all
.PHONY			:	all clean fclean re
