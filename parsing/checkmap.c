/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fortytwo <fortytwo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:20:12 by vmileshk          #+#    #+#             */
/*   Updated: 2025/06/22 19:11:28 by fortytwo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_exten(int argc, char *str)
{
	int	len;

	if (argc != 2)
	{
		write(2, "Error\nIncorect number of arguments.\n", 37);
		write(2, "Usage: ./cub3d map/map_name.ber\n", 32);
		return (1);
	}
	len = ft_strlen(str);
	if (len < 5 || ft_strncmp(str + len - 4, ".cub", 4) != 0)
	{
		write(2, "Not correct file extension .ber\n", 33);
		return (1);
	}
	return (0);
}

int	incorect_char(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while (g->map->map[i])
	{
		j = 0;
		while (g->map->map[i][j])
		{
			if (!allow_char(g->map->map[i][j]))
				return (ft_error(g, "Invalid char in map"));
			j++;
		}
		i++;
	}
	return (0);
}

char	*pad_line_with_spaces(char *line, size_t max_len)
{
	size_t	len;
	size_t	diff;
	size_t	j;
	char	*space;
	char	*tmp;

	len = ft_strlen(line);
	if (len >= max_len)
		return (line);
	diff = max_len - len;
	space = malloc(diff + 1);
	if (!space)
		return (NULL);
	j = 0;
	while (j < diff)
		space[j++] = ' ';
	space[j] = '\0';
	tmp = ft_strjoin(line, space);
	free(space);
	free(line);
	return (tmp);
}

void	add_space(t_map *map)
{
	int		i;
	size_t	max;

	max = count_len_row(map);
	map->col = (int)max;
	i = 0;
	while (map->map[i])
	{
		map->map[i] = pad_line_with_spaces(map->map[i], max);
		if (!map->map[i])
			return ;
		i++;
	}
}

char	**copy_map(char **map, int height)
{
	int		i;
	char	**copy;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		i++;
	}
	copy[height] = NULL;
	return (copy);
}
