// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parsing.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: fortytwo <fortytwo@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/09/26 11:20:12 by vmileshk          #+#    #+#             */
// /*   Updated: 2025/06/19 14:44:21 by fortytwo         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// // #include "../inc/so_long.h"

// int	parsing(t_long *sl, char *argv)
// {
// 	check_exten(argv, sl);
// 	get_x_y(sl, argv);
// 	map_memmory(sl);
// 	get_map(sl, argv);
// 	checkmap(sl);
// 	return (0);
// }

// int	get_x_y(t_long *sl, char *filename)
// {
// 	char	*line;
// 	int		fd;
// 	int		ret;

// 	fd = open(filename, O_RDONLY);
// 	ret = get_next_line(fd, &line);
// 	sl->oldx = ft_strlen(line);
// 	while (line[numberblank(line)] == '1' || line[numberblank(line)] == '0')
// 	{
// 		sl->x = ft_strlen(line);
// 		if (sl->x != sl->oldx)
// 			ft_error(sl, "Map isn't rectangular");
// 		sl->oldx = sl->x;
// 		if (ret != -1)
// 			free(line);
// 		ret = get_next_line(fd, &line);
// 		sl->y++;
// 	}
// 	if (sl->y == 0 || sl->x == 0)
// 		ft_error(sl, "Map isn't well formated");
// 	sl->yscreen = sl->y * 64;
// 	free(line);
// 	sl->xscreen = sl->x * 64;
// 	close(fd);
// 	return (0);
// }

// char	replacechar(char c)
// {
// 	if (c == '0')
// 		return ('a');
// 	if (c == '1')
// 		return ('1');
// 	if (c == 'P')
// 		return ('c');
// 	if (c == 'E')
// 		return ('d');
// 	if (c == 'C')
// 		return ('e');
// 	return (0);
// }

// int	initvar(t_long *sl)
// {
// 	sl->keyboard[BACK] = 0;
// 	sl->keyboard[RED_BUTTON] = 0;
// 	sl->keyboard[ESC] = 0;
// 	sl->keyboard[LEFT] = 0;
// 	sl->keyboard[RIGHT] = 0;
// 	sl->keyboard[ADVANCE] = 0;
// 	sl->bpp = 0;
// 	sl->casein = 0;
// 	sl->casetotal = 0;
// 	sl->y = 0;
// 	sl->x = 0;
// 	sl->collectible = 0;
// 	sl->collectibletotal = 0;
// 	sl->s_line = 0;
// 	sl->maptofree = -1;
// 	sl->move = 0;
// 	sl->playerset = 0;
// 	sl->collectibleset = 0;
// 	sl->exitset = 0;
// 	sl->lastplayer_x = -1;
// 	sl->lastplayer_y = -1;
// 	sl->mlx_ptr = NULL;
// 	return (0);
// }
