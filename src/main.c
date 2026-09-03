/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 11:51:40 by slambert          #+#    #+#             */
/*   Updated: 2026/09/03 12:23:50 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/f_parsing.h"

int		f_exit(char *file, t_db *db, int ret);
bool	start_game(t_db *db, t_color *colors);

int	main(int ac, char *av[])
{
	char	*f;
	t_db	db1;
	t_color	fc[2];

	f = NULL;
	if (f_test_input(ac, av[1]) == false)
		return (1);
	if (f_read_file(&f, av[1]) == false)
		return (1);
	if (db_init(&db1, 1, 1) == false)
		return (ft_putstr_fd("Error\nAlloc\n", 2), f_exit(f, &db1, 1));
	if (f_parse_into_db(&db1, f) == false)
		return (f_exit(f, &db1, 1));
	if (db1.hmap_size != 7)
		return (ft_putstr_fd("Error\nKeys Wrong Nr.\n", 2), f_exit(f, &db1, 1));
	f_init_colors(fc);
	if (f_parse_colors(&db1, fc) == false)
		return (f_exit(f, &db1, 1));
	if (f_parse_map(&db1) == false)
		return (f_exit(f, &db1, 1));
	free(f);
	f = NULL;
	start_game(&db1, fc);
	return (f_exit(f, &db1, 0));
}

int	f_exit(char *file, t_db *db, int ret)
{
	if (file != NULL)
		free(file);
	if (db != NULL)
		free_db(db);
	return (ret);
}
