/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fortytwo <fortytwo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:20:12 by vmileshk          #+#    #+#             */
/*   Updated: 2025/06/16 10:48:24 by fortytwo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

#include <unistd.h>
#include <stdlib.h>

void	ft_error(const char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	// if (cub)
	// 	free_all(cub);
	exit(1);
}


int	check_exten(int argc, char *str)
{
	int	len;
	
	if (argc != 2)
    {
        write(2, "Error\nIncorect number of arguments.\n", 37);
        write(2, "Usage: ./cub3d map/map_name.ber\n", 32);
        return 1;
    }
	len = ft_strlen(str);
	if (len < 5 || ft_strncmp(str + len - 4, ".ber", 4) != 0)
	{
		write(2, "Not correct file extension .ber\n", 33);
		return (1);
	}
	return (0);
}

// int	flood_fill(t_long *sl, int mapy, int mapx)
// {
// 	if (sl->map[mapy][mapx] == 'a' ||
// 	sl->map[mapy][mapx] == 'c' || sl->map[mapy][mapx] == 'd'
// 	|| sl->map[mapy][mapx] == 'e')
// 	{
// 		if (checkaround(mapx, mapy, sl) == 0)
// 			ft_error(sl, "Map isn't surrounded by wall");
// 		flood_fill2(sl, mapy, mapx);
// 		flood_fill(sl, mapy, mapx + 1);
// 		flood_fill(sl, mapy, mapx - 1);
// 		flood_fill(sl, mapy + 1, mapx);
// 		flood_fill(sl, mapy - 1, mapx);
// 	}
// 	return (1);
// }

// void	flood_fill2(t_long *sl, int mapy, int mapx)
// {
// 	if (sl->map[mapy][mapx] == 'a')
// 		sl->map[mapy][mapx] = '0';
// 	if (sl->map[mapy][mapx] == 'c')
// 		sl->map[mapy][mapx] = 'P';
// 	if (sl->map[mapy][mapx] == 'd')
// 	{
// 		sl->map[mapy][mapx] = 'E';
// 		sl->exitparse++;
// 	}
// 	if (sl->map[mapy][mapx] == 'e')
// 	{
// 		sl->map[mapy][mapx] = 'C';
// 		sl->collectibleparse++;
// 	}
// }

// int	checkaround(int mapx, int mapy, t_long *sl)
// {
// 	if (mapy == 0 || mapy == sl->y - 1
// 		|| mapx == 0 || mapx == sl->x - 1)
// 		ft_error(sl, "Map isn't surrounded by wall");
// 	if (check_valid(sl->map[mapy + 1][mapx]) == 0)
// 		return (0);
// 	if (check_valid(sl->map[mapy - 1][mapx]) == 0)
// 		return (0);
// 	if (check_valid(sl->map[mapy][mapx + 1]) == 0)
// 		return (0);
// 	if (check_valid(sl->map[mapy][mapx - 1]) == 0)
// 		return (0);
// 	return (1);
// }

// int	check_wall(t_long *sl)
// {
// 	int	mapx;
// 	int	mapy;

// 	mapy = (int)sl->player_x;
// 	mapx = (int)sl->player_y;
// 	sl->collectibleparse = 0;
// 	sl->exitparse = 0;
// 	flood_fill(sl, mapx, mapy + 1);
// 	flood_fill(sl, mapx, mapy - 1);
// 	flood_fill(sl, mapx + 1, mapy);
// 	flood_fill(sl, mapx, mapy - 1);
// 	if (sl->collectibleparse != sl->collectibletotal)
// 		ft_error(sl, "Collectible isn't on the map");
// 	if (sl->exitparse == 0)
// 		ft_error(sl, "Exit isn't on the map");
// 	return (0);
// }
