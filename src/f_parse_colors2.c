/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parse_colors2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:12:51 by fsitter           #+#    #+#             */
/*   Updated: 2026/08/26 12:49:39 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/f_parsing.h"

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
		db_set(db, "SO", trimmed);
		free(trimmed);
		i++;
	}
	return (true);
}
