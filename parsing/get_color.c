/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fortytwo <fortytwo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:57:36 by fortytwo          #+#    #+#             */
/*   Updated: 2025/06/23 10:52:55 by fortytwo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	count_rdb(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
		i++;
	if (i > 3 || i < 3)
	{
		free_split(rgb);
		return (1);
	}
	else if (!rgb[1] || !rgb[2] || !rgb[0] || rgb[2][0] == '\n'
			|| rgb[2][0] == ' ')
	{
		free_split(rgb);
		return (1);
	}
	return (0);
}

int	parse_color(t_game *g, char *line)
{
	char	**rgb;
	int		r;
	int		g_col;
	int		b;

	rgb = ft_split(line + 2, ',');
	if (!rgb)
		return (ft_error(g, "Failed to split color"));
	if (count_rdb(rgb))
		return (-1);
	r = ft_atoi(rgb[0]);
	g_col = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g_col < 0 || g_col > 255 || b < 0 || b > 255)
	{
		free_split(rgb);
		return (-1);
	}
	free_split(rgb);
	return ((r << 16) | (g_col << 8) | b);
}

int	count_color_exist(t_game *game)
{
	if (game->map->path->c_exist != 1 || game->map->path->f_exist != 1)
		return (ft_error(game, "double color"));
	return (0);
}

void	get_key_word(t_game *game, char *tmp)
{
	if (tmp[0] == 'F' && tmp[1] == ' ')
	{
		game->map->path->floor_color = parse_color(game, tmp);
		game->map->path->f_exist++;
	}
	else if (tmp[0] == 'C' && tmp[1] == ' ')
	{
		game->map->path->ceiling_color = parse_color(game, tmp);
		game->map->path->c_exist++;
	}
}

int	get_color(t_game *game, char *filename)
{
	char	*tmp;
	int		shift;

	if (!game->map->path)
		return (-1);
	game->map->fd = open(filename, O_RDONLY);
	if (game->map->fd < 0)
		return (-1);
	game->map->l = get_next_line(game->map->fd);
	while (game->map->l)
	{
		shift = numberblank(game->map->l);
		tmp = game->map->l + shift;
		get_key_word(game, tmp);
		free(game->map->l);
		game->map->l = get_next_line(game->map->fd);
	}
	free(game->map->l);
	close(game->map->fd);
	get_next_line(-1);
	if (game->map->path->ceiling_color == -1
		|| game->map->path->floor_color == -1)
		return (ft_error(game, "wrong color number"));
	return (count_color_exist(game));
}
