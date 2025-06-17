/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fortytwo <fortytwo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:20:12 by vmileshk          #+#    #+#             */
/*   Updated: 2025/06/16 13:59:10 by fortytwo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"



// char	replacechar(char c)
// {
// 	if (c == '0')
// 		return ('a');
// 	if (c == '1')
// 		return ('1');
// 	if (c == 'P')
// 		return ('c');
// 	if (c == 'E')
// 		return ('d');
// 	if (c == 'C')
// 		return ('e');
// 	return (0);
// }

int	numberblank(char *str)
{
	int	index;

	index = 0;
	while (str[index] == '\t' || str[index] == '\r'
		|| str[index] == '\v' || str[index] == ' ')
		index++;
	return (index);
}
int	get_line(t_map *sl, char *line, int row)
{	
	int	index = 0;

	while (line[index])
	{
		// printf("%c", line[index]);
		// sl->casetotal++;
		sl->map[row][index] = line[index];
		// if (line[index] == 'P')
		// {
		// 	sl->player++;
		// 	sl->player_x = index;
		// 	sl->player_y = nb;
		// }
		// // if (line[index] == 'E')
		// // 	sl->exitset++;
		// // if (line[index] == 'C')
		// // 	sl->collectibletotal++;
		// // if (line[index] != 'P' && line[index] != 'E' && line[index]
		// // 	!= 'C' && line[index] != '1' && line[index] != '0')
		// // 	ft_error(sl, "Wrong character on the map");
		index++;
	}
	sl->map[row][index] = '\0';
	return (0);
}

int count_row(t_map *map, int fd)
{
	char *line;
	int nb = 0;
	line = get_next_line(fd);
	while (line)
	{
		// printf("%s", line);
		free(line);
		line = get_next_line(fd);
		nb++;
	}
	map->row = nb;
	return (nb);
}
// void init_memory_for_map(int fd, t_map *map, int row)
// {
// 	char *line;
// 	int len;
// 	int i = 0;

// 	map->map = malloc(sizeof(char *) * (row + 1));
// 	if (!map->map)
// 		return;

// 	while (i < row && (line = get_next_line(fd)))
// 	{ 
// 		// Measure line length until \0 (not just '\n')
// 		len = 0;
// 		while (line[len] && line[len] != '\n')
// 			len++;

// 		map->col = len;
// 		map->map[i] = malloc(len + 1);
// 		if (!map->map[i])
// 			return ; // you might want to handle malloc failure

// 		// Copy the line content up to len
// 		for (int j = 0; j < len; j++)
// 			map->map[i][j] = line[j];
// 		map->map[i][len] = '\0';

// 		free(line);
// 		i++;
// 	}

// 	map->map[i] = NULL; // optional: null-terminate the map array
// }

int	get_map(t_map *sl, char *filename)
{
	int		fd;
	int		row_count = 0;
	char	*line;
	int		line_len;

	fd = open(filename, O_RDONLY);
	// printf("%d", fd);
	if (fd < 0)
		return (1);

	// Перша фаза — рахуємо кількість рядків
	while ((line = get_next_line(fd)))
	{
		if (line[numberblank(line)] == '1' || line[numberblank(line)] == '0')
			row_count++;
		free(line);
	}
	close(fd);

	sl->row = row_count;
	sl->map = malloc(sizeof(char *) * (row_count + 1));
	if (!sl->map)
		return (1);

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);

	// Друга фаза — читаємо і зберігаємо рядки
	int row = 0;
	while (row < row_count && (line = get_next_line(fd)))
	{
		if (line[numberblank(line)] == '1' || line[numberblank(line)] == '0')
		{
			line_len = 0;
			while (line[line_len] && line[line_len] != '\n')
				line_len++;

			sl->col = line_len;
			sl->map[row] = malloc(line_len + 1);
			if (!sl->map[row])
				return (1);

			for (int j = 0; j < line_len; j++)
				sl->map[row][j] = line[j];
			sl->map[row][line_len] = '\0';

			row++;
		}
		free(line);
	}
	sl->map[row] = NULL;
	close(fd);
	return (0);
}


int	checkmap(t_map *sl)
{
	if (sl->player < 1)
		printf("There must be a player 'P'");
	if (sl->player > 1)
		printf("Multiplayer is not unavailable");
	// if (sl->exitset < 1)
	// 	ft_error(sl, "There must be an exit 'E'");
	// if (sl->exitset > 1)
	// 	ft_error(sl, "There must be only 1 exit");
	// if (sl->collectibletotal == 0)
	// 	ft_error(sl, "There must be a collectible 'C'");
	// check_wall(sl);    receack later
	return (0);
}

void free_map(t_map *map)
{
	int	i;

	if (!map)
		return;

	if (map->map)
	{
		i = 0;
		while (map->map[i])
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
		map->map = NULL;
	}
	if(map->path)
	{
		free(map->path->ea_path);
		free(map->path->no_path);
		free(map->path->so_path);
		free(map->path->we_path);
		free(map->path);		
	}

	if (map->mlx && map->img)
		mlx_destroy_image(map->mlx, map->img);

	if (map->mlx && map->win)
		mlx_destroy_window(map->mlx, map->win);

	if (map->mlx)
	{
		mlx_destroy_display(map->mlx);
		free(map->mlx);
		map->mlx = NULL;
	}

	// НЕ виконуємо free(map), бо це локальна змінна
}

// int main(int argc, char **argv)
// {
// 	(void) argc;
// 	t_map map;
// 	get_map(&map, argv[1]);
// 	int i = 0;
// 	while (map.map[i])
// 	{
// 		printf("%s\n", map.map[i]);
// 		i++;
// 	}
	
// 	free_map(&map);
// }

// int	map_memmory(t_long *sl)
// {
// 	int	i;

// 	i = 0;
// 	sl->map = malloc(sizeof(char *) * sl->y);
// 	while (i < sl->y)
// 	{
// 		sl->map[i] = malloc(sizeof(char) * (sl->x + 1));
// 		i++;
// 	}
// 	sl->maptofree = 1;
// 	return (1);
// }

// int	check_valid(char c)
// {
// 	if (c != '0' && c != 'a' && c != '1' && c != 'P' && c != 'c' && c != 'E'
// 		&& c != 'd' && c != 'C' && c != 'e')
// 		return (0);
// 	return (1);
// }
