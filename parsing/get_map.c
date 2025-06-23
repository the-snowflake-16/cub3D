/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fortytwo <fortytwo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:20:12 by vmileshk          #+#    #+#             */
/*   Updated: 2025/06/23 11:45:30 by fortytwo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_memory(t_map *m, char *file)
{
	int	row_count;

	if (count_map_rows(m, file, &row_count))
		return ;
	m->row = row_count;
	m->map = malloc(sizeof(char *) * (row_count + 1));
	if (!m->map)
		return ;
}

int	copy_map_line(t_map *m, char *line, int row)
{
	int		line_len;
	int		j;

	line_len = 0;
	while (line[line_len] && line[line_len] != '\n')
		line_len++;
	m->col = line_len;
	m->map[row] = malloc(line_len + 1);
	if (!m->map[row])
		return (1);
	j = -1;
	while (++j < line_len)
		m->map[row][j] = line[j];
	m->map[row][line_len] = '\0';
	return (0);
}

void	error_free(t_map *m, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		if (m->map[i])
			free(m->map[i]);
		i++;
	}
	free(m->map);
}

int	handle_map_line(t_map *m, int *row)
{
	if (copy_map_line(m, m->l, *row))
	{
		free(m->l);
		error_free(m, *row);
		return (1);
	}
	(*row)++;
	return (0);
}

int	get_map(t_map *m, char *filename)
{
	int	row;

	init_memory(m, filename);
	m->fd = open(filename, O_RDONLY);
	if (m->fd < 0)
		return (1);
	row = 0;
	m->l = get_next_line(m->fd);
	while (m->l && row < m->row)
	{
		if (is_line_map_data(m->l))
		{
			if (handle_map_line(m, &row))
				return (1);
		}
		free(m->l);
		m->l = get_next_line(m->fd);
	}
	free(m->l);
	m->map[row] = NULL;
	close(m->fd);
	get_next_line(-1);
	return (0);
}
