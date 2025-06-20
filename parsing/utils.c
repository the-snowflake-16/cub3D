/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fortytwo <fortytwo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:06:48 by fortytwo          #+#    #+#             */
/*   Updated: 2025/06/19 19:08:10 by fortytwo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	numberblank(char *str)
{
	int	index;

	index = 0;
	while (str[index] == '\t' || str[index] == '\r'
		|| str[index] == '\v' || str[index] == ' ')
		index++;
	return (index);
}