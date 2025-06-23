#include "../include/cub3d.h"

int	cub_keyup(int k, t_game *g)
{
	if (k == KEY_LEFT)
		g->pl.keys.left_pressed = 0;
	else if (k == KEY_RIGHT)
		g->pl.keys.right_pressed = 0;
	else if (k == KEY_W) // Вперёд
		g->pl.keys.w_pressed = 0;
	else if (k == KEY_A) // Влево
		g->pl.keys.a_pressed = 0;
	else if (k == KEY_S) // Назад
		g->pl.keys.s_pressed = 0;
	else if (k == KEY_D) // Вправо
		g->pl.keys.d_pressed = 0;
	return (0);
}

int	cub_keydown(int k, t_game *g)
{
	if (k == KEY_Q || k == KEY_ESC)
		cub_perror(end, g, NULL, 1);
	else if (k == KEY_LEFT)
		g->pl.keys.left_pressed = 1;
	else if (k == KEY_RIGHT)
		g->pl.keys.right_pressed = 1;
	else if (k == KEY_W)
		g->pl.keys.w_pressed = 1;
	else if (k == KEY_A)
		g->pl.keys.a_pressed = 1;
	else if (k == KEY_S)
		g->pl.keys.s_pressed = 1;
	else if (k == KEY_D)
		g->pl.keys.d_pressed = 1;
	return (0);
}

int	cub_mouse(int x, int y, t_game *g)
{
	if (y != -1)
		g->ray.angle += (x - g->mouse_x) / 3;
	g->mouse_x = x;
	return (0);
}

void	init_attr(t_game *g)
{
	g->win = mlx_new_window(g->mlx, WIN_W, WIN_H, "Cub3D");
	g->win_img.i = mlx_new_image(g->mlx, WIN_W, WIN_H);
	g->win_img.addr = mlx_get_data_addr(g->win_img.i, &g->win_img.bpp, \
		&g->win_img.len_line, &g->win_img.endian);
	g->win_g.i = mlx_new_image(g->mlx, WIN_W, WIN_H);
	g->win_g.addr = mlx_get_data_addr(g->win_g.i, &g->win_g.bpp, \
		&g->win_g.len_line, &g->win_g.endian);
	my_mlx_area_put(&g->win_g, ft_newvector(0, 0), \
		ft_newvector(WIN_W, WIN_H), 0x0000FF00);
	g->win_r.i = mlx_new_image(g->mlx, WIN_W, WIN_H);
	g->win_r.addr = mlx_get_data_addr(g->win_r.i, &g->win_r.bpp, \
		&g->win_r.len_line, &g->win_r.endian);
	my_mlx_area_put(&g->win_r, ft_newvector(0, 0), \
		ft_newvector(WIN_W, WIN_H), 0x00FF0000);
	g->minimap.i = mlx_new_image(g->mlx, g->map->col * SIZE,\
		g->map->row * SIZE);
	g->minimap.addr = mlx_get_data_addr(g->minimap.i, &g->minimap.bpp, \
		&g->minimap.len_line, &g->minimap.endian);
	// g->miniview.i = mlx_new_image(g->mlx, 30 * SIZE, 15 * SIZE);
	// g->miniview.addr = mlx_get_data_addr(g->miniview.i, &g->miniview.bpp, \
	// 	&g->miniview.len_line, &g->miniview.endian);
	// g->miniview.width = 30 * SIZE;
	// g->miniview.height = 15 * SIZE;
}

void	game_init(t_game *g)
{
	init_attr(g);
	ray_init(g);
	mlx_hook(g->win, 02, 1L << 0, cub_keydown, g);
	mlx_hook(g->win, 03, 1L << 1, cub_keyup, g);
	mlx_hook(g->win, 17, 0, cub_exit, g);
	mlx_hook(g->win, 06, 1L << 6, cub_mouse, g);
	mlx_loop_hook(g->mlx, cub_update, g);
	mlx_loop(g->mlx);
}
