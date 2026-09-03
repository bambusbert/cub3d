/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parse_colors2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:12:51 by fsitter           #+#    #+#             */
/*   Updated: 2026/09/03 12:25:12 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/f_parsing.h"

static bool	is_hidden(char *s);

bool	f_comma_after_comma(t_db *db)
{
	char		*key;
	const char	*val;
	int			i;

	key = "F";
	val = db_get(db, key);
	i = 1;
	while (val[i])
	{
		if (val[i - 1] == ',' && val[i] == ',')
			return (false);
		i++;
	}
	key = "C";
	val = db_get(db, key);
	i = 1;
	while (val[i])
	{
		if (val[i - 1] == ',' && val[i] == ',')
			return (false);
		i++;
	}
	return (true);
}

bool	f_trimmer(t_db *db)
{
	char		*link[4];
	const char	*ori;
	int			i;
	char		*trimmed;

	link[0] = "NO";
	link[1] = "EA";
	link[2] = "SO";
	link[3] = "WE";
	i = 0;
	while (i < 4)
	{
		ori = db_get(db, link[i]);
		trimmed = ft_strtrim(ori, " ");
		if (!trimmed)
			return (false);
		if (is_hidden(trimmed) == false)
			return (ft_putstr_fd("Error\nWrong Path or hidden.\n", 2),
				free(trimmed), false);
		db_set(db, link[i], trimmed);
		free(trimmed);
		i++;
	}
	return (true);
}

static bool	is_hidden(char *s)
{
	size_t	i;

	i = ft_strlen(s);
	if (i < 5)
		return (false);
	if (s[i - 5] == '/')
		return (false);
	if (s[i - 4] != '.')
		return (false);
	if (s[i - 3] != 'x')
		return (false);
	if (s[i - 2] != 'p')
		return (false);
	if (s[i - 1] != 'm')
		return (false);
	return (true);
}
