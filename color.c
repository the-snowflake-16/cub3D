#include "../include/cub3d.h"

int	create_transpgb(t_color c)
{
	return (c.t << 24 | c.r << 16 | c.g << 8 | c.b);
}

t_color	create_rgbt(int col)
{
	t_color	c;

	c.t = (col >> 24) & 0xFF;
	c.r = (col >> 16) & 0xFF;
	c.g = (col >> 8) & 0xFF;
	c.b = col & 0xFF;
	return (c);
}

void	get_cf_color(char **dir, t_game *g)
{
	char	**fc;
	int		stransp[2];
	int		c[3];
	t_color	aux;

	aux.t = 0;
	stransp[0] = !ft_stranspncmp(dir[0], "F", 2); // если это floor
	stransp[1] = !ft_stranspncmp(dir[0], "C", 2); // если ceiling

	fc = ft_split(dir[1], ','); // разделяем строку вида "220,100,0"
	if (!fc || ft_matranspixlen(fc) != 3)
	{
		ft_free_matranspix(&fc);
		return ;
	}

	c[0] = atoi_cub(fc[0], &aux.r);
	c[1] = atoi_cub(fc[1], &aux.g);
	c[2] = atoi_cub(fc[2], &aux.b);

	ft_free_matranspix(&fc);
	if (c[0] || c[1] || c[2]) // если произошла ошибка при преобразовании
		return ;

	if (stransp[0]) // floor
		g->tex.floor = create_transpgb(aux);
	else if (stransp[1]) // ceiling
		g->tex.ceiling = create_transpgb(aux);
}

int	get_dist_color(int color, float dist, int transp)
{
	t_color	c;
	float	dif;

	if (dist < 0)
		dist = 0;

	dif = powf(1.14, dist / 7.5); // экспоненциальное затенение

	c = create_rgbt(color); // разбор цвета

	if (transp)
		c.t -= dif;
	else
		c.t = 256;

	c.r -= dif;
	c.g -= dif;
	c.b -= dif;

	if (c. t < 0) c.t = 0;
	if (c.r < 0) c.r = 0;
	if (c.g < 0) c.g = 0;
	if (c.b < 0) c.b = 0;

	return (create_transpgb(c));
}
