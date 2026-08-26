/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parse_colors2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 15:12:51 by fsitter           #+#    #+#             */
/*   Updated: 2026/08/26 12:13:05 by fsitter          ###   ########.fr       */
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
