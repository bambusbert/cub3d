/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_flood_fill_scan.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 12:10:50 by fsitter           #+#    #+#             */
/*   Updated: 2026/08/26 12:11:12 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/f_parsing.h"

void	f_set_neighbours(int *next, int i, int len)
{
	next[0] = i - len;
	next[1] = i + len;
	next[2] = i - 1;
	next[3] = i + 1;
}

bool	f_test_neighbours(char *grid, int *next, bool *changed)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (grid[next[i]] == 32)
			return (false);
		if (grid[next[i]] != '1' && grid[next[i]] != 'x')
		{
			grid[next[i]] = 'x';
			*changed = true;
		}
		i++;
	}
	return (true);
}

bool	f_flood_fill_scan(char *grid, int size, int len, int start_i)
{
	bool	changed;
	int		i;
	int		next[4];

	grid[start_i] = 'x';
	changed = true;
	while (changed)
	{
		changed = false;
		i = -1;
		while (++i < size)
		{
			if (grid[i] != 'x')
				continue ;
			f_set_neighbours(next, i, len);
			if (f_test_neighbours(grid, next, &changed) == false)
				return (false);
		}
	}
	return (true);
}
