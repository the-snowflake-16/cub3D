NAME	= cub3d

MLX			= libmlx.a

SRCS		= maps/* \
			  parsing/* \
			  textures/* 
			  #raycasting.c \
			  utils.c
			  

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

UNAME		:= $(shell uname)

ifeq ($(UNAME), Darwin)
MLX_DIR		= mlx_macos
MLX_INC		= -Imlx_macos
MLX_LIB		= mlx_macos/$(MLX)
MLX_FLAGS	= -Lmlx_macos -lmlx -framework OpenGL -framework AppKit
endif

ifeq ($(UNAME), Linux)
MLX_DIR		= mlx_linux
MLX_INC		= -Imlx_linux
MLX_LIB		= mlx_linux/$(MLX)
MLX_FLAGS	= -Lmlx_linux -lmlx -lmlx_Linux -lXext -lX11 -lm
endif

all: $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(MLX_LIB)
	@echo "cub3d COMPILATION..."
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -g3 -Ofast -o $(NAME) $(SRCS) $(MLX_INC) $(MLX_FLAGS)
	@echo "cub3d SUCCESSFULLY CREATED!"

clean:
	@echo "DELETING OF LAST VERSION..."
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf cub3d.dSYM >/dev/null 2>&1

fclean: clean
	rm -f $(NAME)
	rm -f $(MLX_LIB)

re: fclean all

.PHONY: all clean fclean re
