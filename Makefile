NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude

MLX_DIR = minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

PARSER = parsing/start.c
# somthing rename as you wish
SRC = main.c $(PARSER) $(ENGINE)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(MLX_LIB):
	make -C $(MLX_DIR)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

$(NAME): $(MLX_LIB) $(LIBFT_LIB) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_FLAGS) $(LIBFT_LIB)

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
