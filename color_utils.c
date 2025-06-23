#include "../include/cub3d.h"

int	ft_stranspncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (i < n && (s1[i] || s2[i]))
		return (1);
	return (0);
}

int	ft_matranspixlen(char **matrix)
{
	int	len = 0;

	if (!matrix)
		return (0);
	while (matrix[len])
		len++;
	return (len);
}

void	ft_free_matranspix(char ***matrix)
{
	int	i;

	if (!matrix || !*matrix)
		return ;
	i = 0;
	while ((*matrix)[i])
	{
		free((*matrix)[i]);
		i++;
	}
	free(*matrix);
	*matrix = NULL;
}
