#ifndef CUB_H
#define CUB_H

#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
typedef struct s_map
{
    void *mlx;
    void *win;
    char **map;
    int x;
    int y;
    int player;
} t_map;


void create_map(char **argv);

#endif
