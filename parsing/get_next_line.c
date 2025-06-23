/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fortytwo <fortytwo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:08:57 by fortytwo          #+#    #+#             */
/*   Updated: 2025/06/22 13:30:57 by fortytwo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	has_newline(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*str_join_and_free(char *s1, const char *s2, int read_size)
{
	int		len1;
	int		len2;
	char	*res;
	int		i;
	int		j;

	len1 = str_len(s1);
	len2 = read_size;
	res = malloc(len1 + len2 + 1);
	if (!res)
		return (free(s1), NULL);
	i = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2)
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	return (res);
}

static char	*extract_line(char *s)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (!s || !*s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = s[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*save_remaining(char *s)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
		return (free(s), NULL);
	i++;
	res = malloc(str_len(s + i) + 1);
	if (!res)
		return (NULL);
	j = 0;
	while (s[i])
		res[j++] = s[i++];
	res[j] = '\0';
	free(s);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		buffer[BUFFER_SIZE];
	int			bytes;
	char		*line;

	if (fd == -1)
		return (free(leftover), leftover = NULL, NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes = 1;
	while (!has_newline(leftover) && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(leftover), leftover = NULL, NULL);
		leftover = str_join_and_free(leftover, buffer, bytes);
	}
	line = extract_line(leftover);
	leftover = save_remaining(leftover);
	return (line);
}
