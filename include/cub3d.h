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

typedef struct s_map_state
{
	int	in_map;
	int	map_ended;
	int	row_count;
}	t_map_state;

typedef struct s_path
{
	char *no_path;
	char *so_path;
	char *we_path;
	char *ea_path;
	int floor_color;
	int ceiling_color;
	int no_exist;
	int so_exist;
	int we_exist;
	int ea_exist;
	int f_exist;
	int c_exist;
} t_path;

typedef struct s_map
{
    char **map;
	char **copy;
	int fd;
	char *l;
    int row;
    int col;
    int x;
    int y;
    int player_count;
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
	int				player_x;
	int				player_y;
	// int			fd;
	// int			mouse_x;
	// int			rate;
	// int			neg;
	// long		nframes;
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
	// t_ray		ray;
    t_map       *map;
	// t_player	pl;
	// float		x;
	// float		y;
}				t_game;




float	degree_to_radians(float degree);
void	raycast(t_game *g);
int	check_if_c(char *m, char c, int n0, int n1);
int atoi_cub(const char *nptr, long *nbr);

/* ..parsing/checkmap.c */
int	check_exten(int argc, char *str);
int	incorect_char(t_game *g);
char	*pad_line_with_spaces(char *line, size_t max_len);
void	add_space(t_map *map);
char	**copy_map(char **map, int height);

/* check_valid_map.c */ 
int is_map_full(t_game *g, t_map *map);
int is_map_closed_by_walls(t_game *g);

/* ..parsing_error_and_free.c */ 
void	free_split(char **arr);
int	ft_error(t_game *game, const char *msg);
void	free_map_array(char **map);
void	free_game_map(t_game *game);

/*..parsing/get_color.c */
int	get_color(t_game *game, char *filename);

/*..parsing/get_map.c */
int	get_map(t_map *map, char *filename);

/*..parsing/get_map_utils.c */
int	count_row(t_map *map, int fd);
int	is_line_map_data(char *line);
void	process_map_line(t_map *m, char *line, t_map_state *state);
int	count_map_rows(t_map *m, char *file, int *row_count);

/* ..parsing/get_next_line.c */
char	*get_next_line(int fd); 

/* ..parsing/parsing.c */
int	init_game_data(t_game *game, char *filename);

/* ..parsing/read_path.c */
char	*trim_newline(char *str);
void	init_path(t_path *path);
int	file_exists(const char *filepath);
int	check_path_extension(t_game *game, char *path, char *dir);
int chech_exist(t_game *game, t_path *path); 

/* ..parsing_error.c */ 
int	count_rdb(char **rgb);
int	parse_color(t_game *g, char *line);
int	count_color_exist(t_game *game);
int	get_color(t_game *game, char *filename);

/* ..errors_and.c */
int forbedden(t_game *g);
int error_map(t_game *g);
int	find_player(t_game *g);

/* ..parsing/utils.c */
int	numberblank(char *str);
int	str_len(const char *s);
int	allow_char(char c);
int	count_len_row(t_map *map);
int	is_empty_line(char *line);

#endif
