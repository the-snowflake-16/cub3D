/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fortytwo <fortytwo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:44:49 by fortytwo          #+#    #+#             */
/*   Updated: 2025/06/23 11:47:39 by fortytwo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	count_row(t_map *map, int fd)
{
	char	*line;
	int		nb;

	nb = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		nb++;
	}
	map->row = nb;
	return (nb);
}

int	is_line_map_data(char *line)
{
	int	i;

	i = numberblank(line);
	return (line[i] == '1' || line[i] == '0');
}

void	ft_exit(t_map *m)
{
	printf("Error: map interrupted by non-map line\n");
	free(m->l);
	close(m->fd);
	exit(1);
}

void	process_map_line(t_map *m, char *line, t_map_state *state)
{
	if (is_line_map_data(line))
	{
		if (state->map_ended)
			ft_exit(m);
		state->in_map = 1;
		state->row_count++;
	}
	else if (state->in_map && !is_line_map_data(line))
		state->map_ended = 1;
}

int	count_map_rows(t_map *m, char *file, int *row_count)
{
	t_map_state	state;

	*row_count = 0;
	state.in_map = 0;
	state.map_ended = 0;
	state.row_count = 0;
	m->fd = open(file, O_RDONLY);
	if (m->fd < 0)
		return (1);
	m->l = get_next_line(m->fd);
	while (m->l)
	{
		process_map_line(m, m->l, &state);
		free(m->l);
		m->l = get_next_line(m->fd);
	}
	close(m->fd);
	*row_count = state.row_count;
	return (0);
}
