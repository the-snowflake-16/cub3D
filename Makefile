NAME	= cub3d

MLX			= libmlx.a
LIBFT		= libft/libft.a

SRCS		= $(wildcard parsing/*.c)  main.c
				# utils.c raycasting.c
			  

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

GREEN	= \033[0;32m
RED		= \033[0;31m
YELLOW	= \033[0;33m
BLUE	= \033[0;34m
RESET	= \033[0m

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

LIBFT_INC	= -Ilibft/includes

all: $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(MLX_LIB)
	@echo "$(YELLOW)[INFO]$(RESET) CUB3D COMPILATION...$(RESET)"
	@$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(MLX_INC) $(LIBFT_INC) $(MLX_FLAGS) $(LIBFT)
	@echo "$(GREEN)[SUCCESS] CUB3D SUCCESSFULLY CREATED!$(RESET)"

clean:
	@echo "$(RED)DELETING OF LAST VERSION...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) clean
	rm -rf cub3d.dSYM >/dev/null 2>&1

fclean: clean
	rm -f $(NAME)
	rm -f $(MLX_LIB)

re: fclean all

.PHONY: all clean fclean re
