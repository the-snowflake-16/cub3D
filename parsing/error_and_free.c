/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fortytwo <fortytwo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:45:47 by fortytwo          #+#    #+#             */
/*   Updated: 2025/06/22 19:19:01 by fortytwo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_map_array(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_game_map(t_game *game)
{
	if (!game)
		return ;
	if (game->map)
	{
		if (game->map->path)
		{
			free(game->map->path->no_path);
			free(game->map->path->so_path);
			free(game->map->path->we_path);
			free(game->map->path->ea_path);
			free(game->map->path);
		}
		if (game->map->map)
			free_map_array(game->map->map);
	}
}

int	ft_error(t_game *game, const char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	if (game)
		free_game_map(game);
	return (1);
}
