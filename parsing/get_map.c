/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:20:12 by vmileshk          #+#    #+#             */
/*   Updated: 2024/11/15 16:26:38 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	get_map(t_long *sl, char *filename)
{
	char	*line;
	int		fd;
	int		ret;
	int		nb;

	nb = 0;
	fd = open(filename, O_RDONLY);
	ret = get_next_line(fd, &line);
	while (line[numberblank(line)] == '1' || line[numberblank(line)] == '0')
	{
		get_line(sl, line, nb);
		if (ret != -1)
			free(line);
		ret = get_next_line(fd, &line);
		nb++;
	}
	free(line);
	return (0);
}

int	get_line(t_long *sl, char *line, int nb)
{
	int	index;

	index = 0;
	while (line[index])
	{
		sl->casetotal++;
		sl->map[nb][index] = replacechar(line[index]);
		if (line[index] == 'P')
		{
			sl->playerset++;
			sl->player_x = index;
			sl->player_y = nb;
		}
		if (line[index] == 'E')
			sl->exitset++;
		if (line[index] == 'C')
			sl->collectibletotal++;
		if (line[index] != 'P' && line[index] != 'E' && line[index]
			!= 'C' && line[index] != '1' && line[index] != '0')
			ft_error(sl, "Wrong character on the map");
		index++;
	}
	return (0);
}

int	checkmap(t_long *sl)
{
	if (sl->playerset < 1)
		ft_error(sl, "There must be a player 'P'");
	if (sl->playerset > 1)
		ft_error(sl, "Multiplayer is not unavailable");
	if (sl->exitset < 1)
		ft_error(sl, "There must be an exit 'E'");
	if (sl->exitset > 1)
		ft_error(sl, "There must be only 1 exit");
	if (sl->collectibletotal == 0)
		ft_error(sl, "There must be a collectible 'C'");
	check_wall(sl);
	return (0);
}

int	map_memmory(t_long *sl)
{
	int	i;

	i = 0;
	sl->map = malloc(sizeof(char *) * sl->y);
	while (i < sl->y)
	{
		sl->map[i] = malloc(sizeof(char) * (sl->x + 1));
		i++;
	}
	sl->maptofree = 1;
	return (1);
}

int	check_valid(char c)
{
	if (c != '0' && c != 'a' && c != '1' && c != 'P' && c != 'c' && c != 'E'
		&& c != 'd' && c != 'C' && c != 'e')
		return (0);
	return (1);
}
