/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parse_into_db.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 13:23:03 by fsitter           #+#    #+#             */
/*   Updated: 2026/08/27 11:14:32 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/f_parsing.h"

char	*f_next_line(char *old_line);
bool	f_extract_key_value(t_db *db, char *line, char **key, char **value);
bool	f_is_key(char *line, char **key);
char	*f_skip_ws(char *old_line);

bool	f_parse_into_db(t_db *db, char *file)
{
	char	*line;
	char	*mapstart;
	char	*key;
	char	*value;

	line = file;
	while (*line)
	{
		mapstart = line;
		line = f_skip_ws(line);
		if (*line == '\0')
			break ;
		if (*line == WALL_CHAR || *line == '0')
			return (db_set(db, "MAP", mapstart));
		if (*line != '\n')
		{
			key = NULL;
			value = NULL;
			if (f_extract_key_value(db, line, &key, &value) == false)
				return (false);
		}
		line = f_next_line(line);
	}
	return (true);
}

char	*f_skip_ws(char *old_line)
{
	while (*old_line == '\t' || *old_line == 32)
		old_line++;
	return (old_line);
}

bool	f_extract_key_value(t_db *db, char *line, char **key, char **value)
{
	char	tmp;
	bool	res;

	if (f_is_key(line, key) == false)
		return (ft_putstr_fd("Error\nWrong key.\n", 2), false);
	line += ft_strlen(*key);
	line = f_skip_ws(line);
	*value = line;
	while (*line && *line != '\n')
		line++;
	tmp = *line;
	*line = '\0';
	res = db_set(db, *key, *value);
	*line = tmp;
	return (res);
}

bool	f_is_key(char *line, char **key)
{
	static int	keycount;

	if (line[0] == 'N' && line[1] == 'O' && line[2] == 32)
		*key = "NO";
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == 32)
		*key = "SO";
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == 32)
		*key = "WE";
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == 32)
		*key = "EA";
	else if (line[0] == 'F' && line[1] == 32)
		*key = "F";
	else if (line[0] == 'C' && line[1] == 32)
		*key = "C";
	else
		return (false);
	keycount++;
	if (keycount > 6)
		return (false);
	return (true);
}

char	*f_next_line(char *old_line)
{
	while (*old_line && *old_line != '\n')
		old_line++;
	if (*old_line == '\n')
		old_line++;
	return (old_line);
}
