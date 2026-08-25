/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 11:51:40 by slambert          #+#    #+#             */
/*   Updated: 2026/08/25 16:18:23 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/f_parsing.h"

int		cleanup_and_return(char *file, t_db *db, int ret);
bool	start_game(t_db *db, t_color *colors);

// TODO hier gibt es noch funcheck issues
int	main(int ac, char *av[])
{
	char	*file;
	t_db	db1;
	t_color	fc[2];

	file = NULL;
	if (f_test_input(ac, av[1]) == false)
		return (1);
	if (f_read_file(&file, av[1]) == false)
		return (1);
	if (db_init(&db1, 1, 1) == false)
	    return (ft_putstr_fd("Error\nAllocation.\n", 2), cleanup_and_return(file, &db1, 1));
	if (f_parse_into_db(&db1, file) == false)
		return (cleanup_and_return(file, &db1, 1));
	if (db1.hmap_size != 7)
		return (ft_putstr_fd("Error\nToo many keys.\n", 2),
			cleanup_and_return(file, &db1, 1));
	f_init_colors(fc);
	if (f_parse_colors(&db1, fc) == false)
		return (cleanup_and_return(file, &db1, 1));
	if (f_parse_map(&db1) == false)
		return (cleanup_and_return(file, &db1, 1));
	free(file);
	file = NULL;
		// hat stefan geändert weil ansonsten potentiell double free on error (war funcheck error)
	start_game(&db1, fc);
	return (cleanup_and_return(file, &db1, 0));
}

int	cleanup_and_return(char *file, t_db *db, int ret)
{
	if (file != NULL)
		free(file);
	if (db != NULL)
		free_db(db);
	return (ret);
}
