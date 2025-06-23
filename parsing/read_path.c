/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fortytwo <fortytwo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:14:58 by fortytwo          #+#    #+#             */
/*   Updated: 2025/06/23 12:12:38 by fortytwo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*trim_newline(char *str)
{
	int		len;
	char	*res;
	int		i;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'
			|| str[len - 1] == '\n' || str[len - 1] == '\r'))
		len--;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < len)
		res[i] = str[i];
	res[len] = '\0';
	return (res);
}

void	init_path(t_path *path)
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

int	file_exists(const char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nincorect file name");
		return (1);
	}
	close(fd);
	return (0);
}

int	check_path_extension(t_game *game, char *path, char *dir)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 3, "xpm", 3))
		return (ft_error(game, dir));
	return (0);
}

int	chech_exist(t_game *game, t_path *path)
{
	if (check_path_extension(game, path->no_path, "NO texture ext"))
		return (1);
	if (check_path_extension(game, path->so_path, "SO texture ext"))
		return (1);
	if (check_path_extension(game, path->we_path, "WE texture ext"))
		return (1);
	if (check_path_extension(game, path->ea_path, "EA texture ext"))
		return (1);
	return (0);
}
