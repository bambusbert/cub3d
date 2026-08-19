/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 16:55:28 by slambert          #+#    #+#             */
/*   Updated: 2026/07/17 17:07:42 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// static void	dir_check(char *path)
// {
// 	int	fd;

// 	fd = open(path, O_RDONLY | __O_DIRECTORY);
// 	if (fd >= 0)
// 	{
// 		close(fd);
// 		printf("Error\nPath is a directory\n");
// 		exit(1);
// 	}
// }

// static void	ending_check(char *path)
// {
// 	char	*ending;

// 	if (ft_strlen(path) <= 4)
// 	{
// 		printf("Error\nFile ending is not .cub\n");
// 		exit(1);
// 	}
// 	ending = ft_strrchr(path, '.');
// 	if (!ending || ft_strlen(ending) != 4 || ft_strncmp(ending, ".cub", 4))
// 	{
// 		printf("Error\nFile ending is not .cub\n");
// 		exit(1);
// 	}
// }

// static int	read_check(char *path)
// {
// 	int	fd;

// 	fd = open(path, O_RDONLY);
// 	if (fd <= -1)
// 	{
// 		printf("Error\nError while opening file - not readable\n");
// 		exit(1);
// 	}
// 	return fd;
// }

// void	check_input(int argc, char **argv)
// {
// 	int fd;

// 	if (argc != 2)
// 	{
// 		printf("Error\nwrong number of arguments\n");
// 		exit(1);
// 	}
// 	dir_check(argv[1]);
// 	ending_check(argv[1]);
// 	// check if file is readable
// 	fd = read_check(argv[1]);
// 	// if all checks are OK, call frido_check with fd
// }
