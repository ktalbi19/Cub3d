NAME = cub3D

INC_DIR = ./include/
SRCS_DIR = ./srcs/
MLX_DIR = ./mlx/

CC = gcc
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -L $(MLX_DIR) -lmlx -framework OpenGL -framework Appkit

SRC = calloc.c check_file.c check_map.c colors.c error.c game_update.c\
		game.c key.c main.c move.c raycasting.c set_dir.c split.c\
		utils_lib.c utils.c

SRCS = $(addprefix $(SRCS_DIR), $(SRC))
OBJS = $(SRCS:.c=.o)

$(NAME)	: $(OBJS)
		make -C $(MLX_DIR)
		$(CC) -o $(NAME) $(OBJS) -I $(INC_DIR) $(LIBFLAGS)

all:	$(NAME)

clean:	
		make -C $(MLX_DIR) clean
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re:	clean all

.PHONY: all clean fclean re