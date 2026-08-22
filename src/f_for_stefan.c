/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_for_stefan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 11:49:46 by slambert          #+#    #+#             */
/*   Updated: 2026/08/22 11:49:47 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/f_parsing.h"

char	**free_2d_arr(char **stefan);
char	**create_2d_arr(char *s, int k, int x, int y);
void	set_stefan(char *dest, char *src);

bool	for_fortnite_and_stefan(t_db *db, t_color *colors)
{
	const char	*s;
	char		**for_stefan;
	int			x;
	int			y;
	bool		ret;

	ret = true;
	s = db_get(db, "TESTMAP");
	x = f_atoll((char *)db_get(db, "x"));
	y = f_atoll((char *)db_get(db, "y"));
	for_stefan = create_2d_arr((char *)s, 0, x, y);
	if (!for_stefan)
		return (false);
	ret = start_graphical_stuff(db, for_stefan, colors);
	for_stefan = free_2d_arr(for_stefan);
	return (ret);
}

char	**free_2d_arr(char **stefan)
{
	int	i;

	i = 0;
	while (stefan[i])
	{
		free(stefan[i]);
		i++;
	}
	free(stefan);
	return (NULL);
}

char	**create_2d_arr(char *s, int k, int x, int y)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	map = ft_calloc(sizeof(char *), y + 1);
	if (!map)
		return (ft_putstr_fd("Error\nAllocation.\n", 2), NULL);
	while (i < y)
	{
		map[i] = ft_calloc(sizeof(char), x + 1);
		if (!map[i])
			return (ft_putstr_fd("Error\nAllocation.\n", 2), free_2d_arr(map));
		j = 0;
		while (j < x)
		{
			set_stefan(&map[i][j], &s[k]);
			j++;
			k++;
		}
		i++;
	}
	return (map);
}

void	set_stefan(char *dest, char *src)
{
	if (*src == ' ')
		*dest = WALL_CHAR;
	else
		*dest = *src;
}
