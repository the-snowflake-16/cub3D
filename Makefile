NAME = cub3d

CC = gcc
CFLAGS =  -Wextra -Werror -Iinclude

MLX_DIR = minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

SRC = src/main.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(MLX_LIB):
	make -C $(MLX_DIR)

$(NAME): $(MLX_LIB) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_FLAGS)

clean:
	rm -f $(OBJ)
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
