#ifndef CUB3D_H
#define CUB3D_H

#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
# include "keycodes.h"
# include <mlx.h>
# include "get_next_line.h"
# include "my_mlx.h"
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

typedef struct s_ray
{
	float	incre_angle;
	float	angle;
	float	cos;
	float	sin;
	float	hfov;
	float	limше;
	int		precision;
}				t_ray;

typedef struct s_game
{
	int			fd;
	char		**map;
	int			height;
	int			width;
	int			mouse_x;
	int			rate;
	int			neg;
	long		nframes;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		win_img;
	t_img		win_g;
	t_img		win_r;
	t_img		minimap;
	t_img		miniview;
	t_img		*scope;
	t_tex		tex;
	t_ray		ray;
	t_player	pl;
	float		x;
	float		y;
}				t_game;

// typedef struct s_map >>> !!! Если ты не против, давай основную структуру назовем s_game? <<<
// {
//     void *mlx;
//     void *win;
//     char **map;
//     int x;
//     int y;
//     int player;
// } t_map;


void create_map(char **argv);

float	degree_to_radians(float degree);
void	raycast(t_game *g);
int	check_if_c(char *m, char c, int n0, int n1);
int atoi_cub(const char *nptr, long *nbr);


#endif
