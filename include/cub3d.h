#ifndef CUB3D_H
#define CUB3D_H

#include "../libft/libft.h"
#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
# include "keycodes.h"
// # include <mlx.h>
// # include "get_next_line.h"   i don`t have get_next_line in myown laptop so i created new littel one in parser if you need you can use or add yor get_nex_line 
// # include "my_mlx.h"
# include <math.h>

# ifndef WIN_H
#  define WIN_H 480
# endif

# ifndef WIN_W
#  define WIN_W 640
# endif

# ifndef SIZE
#  define SIZE 7
# endif

#ifndef TILE_SIZE
#  define TILE_SIZE 32
# endif

#ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct s_ray
{
	float	incre_angle;
	float	angle;
	float	cos;
	float	sin;
	float	hfov;
	float	limit;
	int		precision;
}				t_ray;

typedef struct s_path
{
	char *no_path;
	char *so_path;
	char *we_path;
	char *ea_path;
	int floor_color;
	int ceiling_color;
} t_path;

typedef struct s_map
{
    char **map;
    int row;
    int col;
    int x;
    int y;
    int player;
    double			casetotal;
    int				player_x;
	int				player_y;
    t_path      *path;
} t_map;

typedef struct s_key
{
	int	w_pressed;
	int	a_pressed;
	int	s_pressed;
	int	d_pressed;
	int	left_pressed;
	int	right_pressed;
}				t_key;


typedef struct s_player
{
	float	x;
	float	y;
	char	dir;
	float	speed;
	int		door_cooldown;
	t_key	keys;
}				t_player;

typedef struct s_game
{
	int			fd;
	int			height;
	int			width;
	int			mouse_x;
	int			rate;
	int			neg;
	long		nframes;
	void		*mlx;
	void		*win;
    void        *img;

	// t_img		win_img;
	// t_img		win_g;
	// t_img		win_r;
	// t_img		minimap;
	// t_img		miniview;
	// t_img		*scope;
	// t_tex		tex;
	t_ray		ray;
    t_map       *map;
	// t_player	pl;
}				t_game;


/* ..parsing/checkmap.c */
int	check_exten(int argc, char *str);

float	degree_to_radians(float degree);
void	raycast(t_game *g);
int	check_if_c(char *m, char c, int n0, int n1);
int atoi_cub(const char *nptr, long *nbr);


/* ..parsing/start.c */
void init_window(int argc, char **argv)
;

/*..parsing/get_map.c */
int	get_map(t_map *sl, char *filename);
void free_game(t_game *game);

/* ..parsing/get_next_line.c */
char	*get_next_line(int fd); 

/* ..parsing/read_path.c */
int get_path(t_path *path, char *filename); 
int get_color(t_path *path, char *filename);
#endif
