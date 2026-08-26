/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_read_file.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 15:38:49 by fsitter           #+#    #+#             */
/*   Updated: 2026/08/26 12:18:28 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef F_READ_FILE_H
# define F_READ_FILE_H

# define READ_SIZE 1023

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <unistd.h>

// struct prototypes

typedef struct s_read	t_read;

typedef struct s_read
{
	size_t				position;
	size_t				read_size;
	size_t				buffer_size;
	char				*buffer;
	ssize_t				read_bytes;
}						t_read;

// prototypes

// f_read_file.c
bool					f_read_file(char **dest, char *filename);

#endif