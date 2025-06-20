/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fortytwo <fortytwo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:14:58 by fortytwo          #+#    #+#             */
/*   Updated: 2025/06/20 12:05:39 by fortytwo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int is_empty_line(char *line)
{
	if (!line)
		return 1;
	int i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return 0;
		i++;
	}
	return 1;
}

#include <string.h>
char *trim_newline(char *str)
{
    int len;
    char *res;

    if (!str)
        return NULL;

    len = ft_strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\n' || str[len - 1] == '\r'))
        len--;

    res = malloc(len + 1);
    if (!res)
        return NULL;

    for (int i = 0; i < len; i++)
        res[i] = str[i];
    res[len] = '\0';

    return res;
    
}

void init_path(t_path *path)
{
    path->ceiling_color = -1;
    path->floor_color = -1;
    path->ea_exist = 0;
    path->no_exist = 0;
    path->so_exist = 0;
    path->we_exist = 0;
    path->c_exist = 0;
    path->f_exist = 0;
    path->ea_path = NULL;
    path->no_path = NULL;
    path->so_path = NULL;
    path->we_path = NULL;
}

int file_exists(const char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    if (fd < 0)
        return 1;
    close(fd);
    return 0;
}

int check_path(t_game *game)
{
	t_path *path;

	if (!game || !game->map || !game->map->path)
		return ft_error(game, "Missing path structure");

	path = game->map->path;
	if (path->no_exist > 1)
		return ft_error(game, "DOUBLE NO");
	if (path->so_exist > 1)
		return ft_error(game, "DOUBLE SO");
	if (path->we_exist > 1)
		return ft_error(game, "DOUBLE WE");
	if (path->ea_exist > 1)
		return ft_error(game, "DOUBLE EA");

	if (!path->no_path || !path->so_path || !path->we_path || !path->ea_path)
		return ft_error(game, "Missing texture path string");
    if (file_exists(path->no_path))
        return ft_error(game, "NO texture file does not exist");
    if (file_exists(path->so_path))
        return ft_error(game, "SO texture file does not exist");
    if (file_exists(path->we_path))
        return ft_error(game, "WE texture file does not exist");
    if (file_exists(path->ea_path))
        return ft_error(game, "EA texture file does not exist");       
    if  (ft_strncmp(path->no_path + ft_strlen(path->no_path) - 3, "xpm", 3))
            return ft_error(game, "NO textures not xpm");
    if  (ft_strncmp(path->ea_path + ft_strlen(path->ea_path) - 3, "xpm", 3))
        return ft_error(game, "EA textures not xpm");
    if  (ft_strncmp(path->we_path + ft_strlen(path->we_path) - 3, "xpm", 3))
            return ft_error(game, "WE textures not xpm");
    if  (ft_strncmp(path->so_path + ft_strlen(path->so_path) - 3, "xpm", 3))
            return ft_error(game, "SO textures not xpm");
	return 0;
}


int get_path(t_game *game, char *filename)
{
    char    *line;
    char    *tmp;
    int     fd;
    int     shift;
    t_path  *path;

    if (!game || !game->map || !game->map->path)
        return ft_error(game, "Path structure not initialized");

    path = game->map->path;
    init_path(path);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return ft_error(game, "Cannot open file");
    line = get_next_line(fd);
    while (line)
    {
        if (is_empty_line(line))
        {
            free(line);
            line = get_next_line(fd);
            continue;
        }
        shift = numberblank(line);
        tmp = line + shift;
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
        free(line);
        line = get_next_line(fd);
    }

    close(fd);
    get_next_line(-1);
    return check_path(game);
}

void free_split(char **arr)
{
    int i = 0;
    if (!arr)
        return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

int	parse_color(t_game *g, char *line)
{
	int	r, g_col, b;
	char **rgb;
	int i;

	rgb = ft_split(line + 2, ',');
	if (!rgb)
		return ft_error(g, "Failed to split color");

	i = 0;
	while (rgb[i])
		i++;

	if (i != 3)
	{
		free_split(rgb);
		return -1;
	}

	r = ft_atoi(rgb[0]);
	g_col = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);

	if (r < 0 || r > 255 || g_col < 0 || g_col > 255 || b < 0 || b > 255)
	{
		free_split(rgb);
		return -1;
	}

	free_split(rgb);
	return ((r << 16) | (g_col << 8) | b);
}

int count_color_exist(t_game *game)
{
    if(game->map->path->c_exist != 1 || game->map->path->f_exist != 1)
        return(ft_error(game, "double color"));
    return (0);
}

int get_color(t_game *game, char *filename)
{
    char *line;
    int fd;

    if (!game->map->path)
        return -1;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return -1;

    line = get_next_line(fd);

    while (line)
    {
        int shift = numberblank(line);
        char *tmp = line + shift;
        if(tmp[0] == 'F' && tmp[1] == ' ')
        {
            game->map->path->floor_color = parse_color(game, tmp);
            game->map->path->f_exist++;
        }

        else if (tmp[0] == 'C' && tmp[1] == ' ')
        {
            game->map->path->ceiling_color = parse_color(game, tmp);
            game->map->path->c_exist++;
        }

        free(line);
        line = get_next_line(fd);
    }
    free(line);
    close(fd);
    get_next_line(-1);
    if(game->map->path->ceiling_color == -1 || game->map->path->floor_color == -1)
        return(ft_error(game, "wrong color number"));
    return (count_color_exist(game));
}
