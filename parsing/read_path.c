/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fortytwo <fortytwo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:14:58 by fortytwo          #+#    #+#             */
/*   Updated: 2025/06/17 18:59:38 by fortytwo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int get_path(t_path *path, char *filename)
{
    char *line;
    int fd;

    if (!path)
        return -1;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return -1;

    line = get_next_line(fd);
    while (line && (!ft_strncmp(line, "NO", 2) || (line && !ft_strncmp(line, "SO", 2)) ||
                    (line && !ft_strncmp(line, "WE", 2)) || (line && !ft_strncmp(line, "EA", 2))))
    {
        if (!ft_strncmp(line, "NO", 2))
            path->no_path = ft_strdup(line + 3);
        else if (!ft_strncmp(line, "SO", 2))
            path->so_path = ft_strdup(line + 3);
        else if (!ft_strncmp(line, "WE", 2))
            path->we_path = ft_strdup(line + 3);
        else if (!ft_strncmp(line, "EA", 2))
            path->ea_path = ft_strdup(line + 3);
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    close(fd);
    get_next_line(-1);
    return 0;
}

int	parse_color(char *line)
{
	int	r, g, b;
	char **rgb;

	rgb = ft_split(line + 2, ',');
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);

	// очищення пам'яті
	// free_split(rgb);
	return ((r << 16) | (g << 8) | b);
}

int get_color(t_path *path, char *filename)
{
    char *line;
    int fd;

    if (!path)
        return -1;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return -1;

    line = get_next_line(fd);
    while ((line && (!ft_strncmp(line, "F", 1))) || (line && (!ft_strncmp(line, "C", 1))))
    {
        if(line[0] == 'F' && line[1] == ' ')
            path->floor_color = parse_color(line);
        else if (line[0] == 'C' &&line[1] == ' ')
            path->ceiling_color = parse_color(line);
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    close(fd);
    get_next_line(-1);
    return (0);
}
