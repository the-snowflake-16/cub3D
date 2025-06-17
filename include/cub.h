#ifndef CUB_H
#define CUB_H

#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define TILE_SIZE 32
#define BUFFER_SIZE 32

typedef struct s_path
{
	char *no_path;
	char *so_path;
	char *we_path;
	char *ea_path;
	int floor_color;
	int ceiling_color;
} t_path;

// typedef struct s_map
// {
//     t_path *path;
//     void *mlx;
//     void *win;
//     void *img;
//     char **map;
//     int row;
//     int col;
//     int x;
//     int y;
//     int player;
//     double			casetotal;
//     	int				player_x;
// 	int				player_y;
// } t_map;


/* ..parsing/checkmap.c */
int	check_exten(int argc, char *str);

/* ..parsing/start.c */
void init_window(int argc, char **argv)
;

/*..parsing/get_map.c */
int	get_map(t_map *sl, char *filename);
void free_map(t_map *map);

/* ..parsing/get_next_line.c */
char	*get_next_line(int fd); 

/* ..parsing/read_path.c */
int get_path(t_path *path, char *filename); 
int get_color(t_path *path, char *filename);
#endif
