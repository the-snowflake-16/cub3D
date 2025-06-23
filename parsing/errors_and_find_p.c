/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_and_find_p.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fortytwo <fortytwo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 07:41:09 by fortytwo          #+#    #+#             */
/*   Updated: 2025/06/23 12:02:14 by fortytwo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	forbidden(t_game *g)
{
	int	contain_0;
	int	i;
	int	j;

	contain_0 = 0;
	i = 0;
	while (g->map->map[i])
	{
		j = 0;
		while (g->map->map[i][j])
		{
			if (g->map->map[i][j] == '0')
				contain_0 = 1;
			j++;
		}
		i++;
	}
	if (!contain_0)
	{
		ft_error(g, "Map without space");
		return (1);
	}
	return (0);
}

int	error_map(t_game *g)
{
	if (forbidden(g))
		return (1);
	return (0);
}

static void	count_players(t_game *g)
{
	int	x;
	int	y;

	g->map->player_count = 0;
	x = 0;
	while (g->map->map[x])
	{
		y = 0;
		while (g->map->map[x][y])
		{
			if (g->map->map[x][y] == 'N' || g->map->map[x][y] == 'E'
				|| g->map->map[x][y] == 'W' || g->map->map[x][y] == 'S')
			{
				g->map->player_count++;
				g->player_x = x;
				g->player_y = y;
			}
			y++;
		}
		x++;
	}
}

int	find_player(t_game *g)
{
	count_players(g);
	if (g->map->player_count < 1)
		return (ft_error(g, "NO player"));
	if (g->map->player_count > 1)
		return (ft_error(g, "More then one player"));
	return (0);
}
