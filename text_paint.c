#include "../include/cub3d.h"

t_img	*texture_get(t_game *g)
{
	t_img	*i;
	float	ray_cos;
	float	ray_sin;

	ray_cos = g->ray.cos;
	if (ray_cos < 0)
		ray_cos = -ray_cos;
	ray_sin = g->ray.sin;
	if (ray_sin < 0)
		ray_sin = -ray_sin;
	
	i = g->tex.b; //base text

	if (g->map->map[(int)(g->y - ray_sin)][(int)g->x] != '1')
		i = g->tex.n->content;
	else if (g->map->map[(int)(g->y + ray_sin)][(int)g->x] != '1')
		i = g->tex.s->content;
	else if (g->map->map[(int)g->y][(int)(g->x + ray_cos)] != '1')
		i = g->tex.e->content;
	else if (g->map->map[(int)g->y][(int)(g->x - ray_cos)] != '1')
		i = g->tex.w->content;
	return (i);
}

int	get_tex_color(t_game *g, t_img *i, int z)
{
	int	color;

	color = 0x00000000; // чёрный по умолчанию

	if (g->map->map[(int)g->y][(int)g->x] == '1') // если стена
		color = my_mlx_pixel_get(i,
			(int)(i->width * (g->x + g->y)) % i->width, z); // берёт координату X по модулю ширины
	else if (g->map->map[(int)g->y][(int)g->x] == 'c') // если "спец" стена
		color = 0x00FF0000; // красный

	return (color);
}

void	draw_texture(t_game *g, t_img *i, int ray_count, int wall_height)
{
	float	dy;
	float	ds;
	float	cy[2];
	int		z;
	int		color;

	dy = ((float)wall_height * 2) / (float)i->height;
	// dy — сколько пикселей по экрану приходится на 1 пиксель текстуры по Y

	ds = ((float)WIN_H / 2) - (float)wall_height;
	// ds — начальная вертикальная позиция текстуры (где стена начинается по Y)

	cy[1] = ds; // текущая координата по Y

	z = -1;
	while (++z < i->height) // перебираем пиксели текстуры по вертикали
	{
		color = get_tex_color(g, i, z); // цвет из текстуры
		color = get_dist_color(color, ds, 0); // корректируем цвет по расстоянию (затенение)

		cy[0] = cy[1]; // старт от текущего Y
		while (cy[0] < cy[1] + dy) // рисуем dy пикселей этого цвета на экране
		{
			if (cy[0] >= 0 && cy[0] < (float)WIN_H)
				my_mlx_pixel_put(&g->win_img, ray_count, cy[0], color);
			cy[0]++;
		}
		cy[1] += dy; // двигаемся по Y
	}
}

void	cub_draw(t_game *g, int ray_count, float dis)
{
	int		wall_height;
	float	ds;
	int		j;

	wall_height = (int)(WIN_H / (1.5 * dis));
	// чем ближе стена — тем выше. 1.5 — поправка масштаба

	ds = ((float)WIN_H / 2) - (float)wall_height;
	// ds — где по вертикали начинается текстура стены

	j = -1;
	while (++j < WIN_H) // идём по всем пикселям экрана вертикально
	{
		if (j < ds)
			// если выше стены — рисуем потолок
			my_mlx_pixel_put(&g->win_img, ray_count, j,
				get_dist_color(g->tex.ceiling, j, 0));
		else if (j >= (WIN_H / 2) + wall_height)
			// если ниже стены — рисуем пол
			my_mlx_pixel_put(&g->win_img, ray_count, j,
				get_dist_color(g->tex.floor, WIN_H - j, 0));
	}

	// после потолка и пола рисуем саму стену
	draw_texture(g, texture_get(g), ray_count, wall_height);
}