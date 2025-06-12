/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:20:12 by vmileshk          #+#    #+#             */
/*   Updated: 2024/11/15 16:25:15 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	check_exten(char *str, t_long *sl)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (str[i - 1] == 'r' && str[i - 2] == 'e'
		&& str[i - 3] == 'b' && str[i - 4] == '.')
	{
		i = open(str, O_RDONLY);
		if (i == -1)
			ft_error(sl, "Filename isn't correct");
		else
			close(i);
		return (0);
	}
	ft_error(sl, "Not correct file extension .ber");
	return (0);
}

int	flood_fill(t_long *sl, int mapy, int mapx)
{
	if (sl->map[mapy][mapx] == 'a' ||
	sl->map[mapy][mapx] == 'c' || sl->map[mapy][mapx] == 'd'
	|| sl->map[mapy][mapx] == 'e')
	{
		if (checkaround(mapx, mapy, sl) == 0)
			ft_error(sl, "Map isn't surrounded by wall");
		flood_fill2(sl, mapy, mapx);
		flood_fill(sl, mapy, mapx + 1);
		flood_fill(sl, mapy, mapx - 1);
		flood_fill(sl, mapy + 1, mapx);
		flood_fill(sl, mapy - 1, mapx);
	}
	return (1);
}

void	flood_fill2(t_long *sl, int mapy, int mapx)
{
	if (sl->map[mapy][mapx] == 'a')
		sl->map[mapy][mapx] = '0';
	if (sl->map[mapy][mapx] == 'c')
		sl->map[mapy][mapx] = 'P';
	if (sl->map[mapy][mapx] == 'd')
	{
		sl->map[mapy][mapx] = 'E';
		sl->exitparse++;
	}
	if (sl->map[mapy][mapx] == 'e')
	{
		sl->map[mapy][mapx] = 'C';
		sl->collectibleparse++;
	}
}

int	checkaround(int mapx, int mapy, t_long *sl)
{
	if (mapy == 0 || mapy == sl->y - 1
		|| mapx == 0 || mapx == sl->x - 1)
		ft_error(sl, "Map isn't surrounded by wall");
	if (check_valid(sl->map[mapy + 1][mapx]) == 0)
		return (0);
	if (check_valid(sl->map[mapy - 1][mapx]) == 0)
		return (0);
	if (check_valid(sl->map[mapy][mapx + 1]) == 0)
		return (0);
	if (check_valid(sl->map[mapy][mapx - 1]) == 0)
		return (0);
	return (1);
}

int	check_wall(t_long *sl)
{
	int	mapx;
	int	mapy;

	mapy = (int)sl->player_x;
	mapx = (int)sl->player_y;
	sl->collectibleparse = 0;
	sl->exitparse = 0;
	flood_fill(sl, mapx, mapy + 1);
	flood_fill(sl, mapx, mapy - 1);
	flood_fill(sl, mapx + 1, mapy);
	flood_fill(sl, mapx, mapy - 1);
	if (sl->collectibleparse != sl->collectibletotal)
		ft_error(sl, "Collectible isn't on the map");
	if (sl->exitparse == 0)
		ft_error(sl, "Exit isn't on the map");
	return (0);
}
