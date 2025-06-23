/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fortytwo <fortytwo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:55:46 by fortytwo          #+#    #+#             */
/*   Updated: 2025/06/23 13:18:09 by fortytwo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_path(t_game *game)
{
	t_path	*path;

	if (!game || !game->map || !game->map->path)
		return (ft_error(game, "Missing path structure"));
	path = game->map->path;
	if (path->no_exist > 1 || path->so_exist > 1
		|| path->we_exist > 1 || path->ea_exist > 1)
		return (ft_error(game, "Error texture"));
	if (!path->no_path || !path->so_path
		|| !path->we_path || !path->ea_path)
		return (ft_error(game, "Missing texture path"));
	if (file_exists(path->no_path))
		return (ft_error(game, "NO texture file missing"));
	if (file_exists(path->so_path))
		return (ft_error(game, "SO texture file missing"));
	if (file_exists(path->we_path))
		return (ft_error(game, "WE texture file missing"));
	if (file_exists(path->ea_path))
		return (ft_error(game, "EA texture file missing"));
	return (chech_exist(game, path));
}

void	save_texture_path(t_path *path, char *tmp)
{
	if (!ft_strncmp(tmp, "NO", 2))
	{
		if (!path->no_path)
			path->no_path = trim_newline(tmp + 3);
		path->no_exist++;
	}
	else if (!ft_strncmp(tmp, "SO", 2))
	{
		if (!path->so_path)
			path->so_path = trim_newline(tmp + 3);
		path->so_exist++;
	}
	else if (!ft_strncmp(tmp, "WE", 2))
	{
		if (!path->we_path)
			path->we_path = trim_newline(tmp + 3);
		path->we_exist++;
	}
	else if (!ft_strncmp(tmp, "EA", 2))
	{
		if (!path->ea_path)
			path->ea_path = trim_newline(tmp + 3);
		path->ea_exist++;
	}
}

int	get_path(t_game *game, char *filename)
{
	char	*tmp;
	int		shift;

	if (!game || !game->map || !game->map->path)
		return (ft_error(game, "Path structure not initialized"));
	init_path(game->map->path);
	game->map->fd = open(filename, O_RDONLY);
	if (game->map->fd < 0)
		return (ft_error(game, "Cannot open file"));
	game->map->l = get_next_line(game->map->fd);
	while (game->map->l)
	{
		if (!is_empty_line(game->map->l))
		{
			shift = numberblank(game->map->l);
			tmp = game->map->l + shift;
			save_texture_path(game->map->path, tmp);
		}
		free(game->map->l);
		game->map->l = get_next_line(game->map->fd);
	}
	close(game->map->fd);
	get_next_line(-1);
	return (check_path(game));
}

int	init_game_data(t_game *game, char *filename)
{
	game->map->path = malloc(sizeof(t_path));
	if (!game->map->path)
		return (1);
	if (get_path(game, filename))
		return (1);
	if (get_color(game, filename))
		return (1);
	if (incorect_char(game))
		return (1);
	add_space(game->map);
	if (is_map_full(game, game->map))
		return (1);
	if (is_map_closed_by_walls(game))
		return (1);
	if (find_player(game))
		return (1);
	if (error_map(game))
		return (1);
	return (0);
}
