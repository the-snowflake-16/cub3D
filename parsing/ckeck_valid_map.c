/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ckeck_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fortytwo <fortytwo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:24:59 by fortytwo          #+#    #+#             */
/*   Updated: 2025/06/23 10:56:47 by fortytwo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	flood_fill(t_map *map, int x, int y, int *error)
{
	char	c;

	if (x < 0 || y < 0 || x >= map->col || y >= map->row)
		return ;
	c = map->copy[y][x];
	if (c == '1' || c == 'F')
		return ;
	if (c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
		*error = 1;
	map->copy[y][x] = 'F';
	flood_fill(map, x + 1, y, error);
	flood_fill(map, x - 1, y, error);
	flood_fill(map, x, y + 1, error);
	flood_fill(map, x, y - 1, error);
}

int	is_map_full(t_game *g, t_map *map)
{
	int		error;
	int		x;
	int		y;

	error = 0;
	map->copy = copy_map(map->map, map->row);
	if (!map->copy)
		return (ft_error(g, "Copy failed"));
	y = 0;
	while (y < map->row)
	{
		x = 0;
		while (x < map->col)
		{
			if (map->copy[y][x] == ' ')
				flood_fill(map, x, y, &error);
			x++;
		}
		y++;
	}
	free_map_array(map->copy);
	if (error)
		return (ft_error(g, "Map is not closed"));
	return (0);
}

int	check_top_and_bottom(t_game *g, int width, int height)
{
	int		x;
	char	**map;

	x = 0;
	map = g->map->map;
	while (x < width)
	{
		if (map[0][x] != '1' && map[0][x] != ' ')
			return (ft_error(g, "Top border not closed"));
		if (map[height - 1][x] != '1'
			&& map[height - 1][x] != ' ')
			return (ft_error(g, "Bottom border not closed"));
		x++;
	}
	return (0);
}

int	check_left_and_right(t_game *g, int width, int height)
{
	int		y;
	char	**map;

	y = 0;
	map = g->map->map;
	while (y < height)
	{
		if (map[y][0] != '1' && map[y][0] != ' ')
			return (ft_error(g, "Left border not closed"));
		if (map[y][width - 1] != '1'
			&& map[y][width - 1] != ' ')
			return (ft_error(g, "Right border not closed"));
		y++;
	}
	return (0);
}

int	is_map_closed_by_walls(t_game *g)
{
	int	res;
	int	width;
	int	height;

	width = g->map->col;
	height = g->map->row;
	res = check_left_and_right(g, width, height);
	if (res == 0)
		res = check_top_and_bottom(g, width, height);
	return (res);
}
