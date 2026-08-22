/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 16:55:28 by slambert          #+#    #+#             */
/*   Updated: 2026/08/22 11:48:06 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//TODO remove
// static void	dir_check(char *path)
// {
// 	int	fd;

// 	fd = open(path, O_RDONLY | __O_DIRECTORY);
// 	if (fd >= 0)
// 	{
// 		close(fd);
// 		ft_putstr_fd("Error\nPath is a directory\n", 2);
// 		exit(1);
// 	}
// }

// static void	ending_check(char *path)
// {
// 	char	*ending;

// 	if (ft_strlen(path) <= 4)
// 	{
// 		ft_putstr_fd("Error\nFile ending is not .cub\n", 2);
// 		exit(1);
// 	}
// 	ending = ft_strrchr(path, '.');
// 	if (!ending || ft_strlen(ending) != 4 || ft_strncmp(ending, ".cub", 4))
// 	{
// 		ft_putstr_fd("Error\nFile ending is not .cub\n", 2);
// 		exit(1);
// 	}
// }

// static int	read_check(char *path)
// {
// 	int	fd;

// 	fd = open(path, O_RDONLY);
// 	if (fd <= -1)
// 	{
// 		ft_putstr_fd("Error\nError while opening file - not readable\n", 2);
// 		exit(1);
// 	}
// 	return (fd);
// }

// void	check_input(int argc, char **argv)
// {
// 	int	fd;

// 	if (argc != 2)
// 	{
// 		ft_putstr_fd("Error\nwrong number of arguments\n", 2);
// 		exit(1);
// 	}
// 	dir_check(argv[1]);
// 	ending_check(argv[1]);
// 	fd = read_check(argv[1]);
// }
