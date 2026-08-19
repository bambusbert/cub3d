/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_read_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 15:44:43 by fsitter           #+#    #+#             */
/*   Updated: 2026/08/19 18:46:18 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "f_read_file.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static int	f_open_file(const char *filename);
static char	*f_read_from_file(int fd);
static bool	f_init_r(t_read *r);
static char	*f_resize(t_read *r);

bool	f_read_file(char **dest, char *filename)
{
	int		fd;
	char	*buffer;

	fd = f_open_file(filename);
	if (fd == -1)
		return (printf("Error opening file.\n"), false);
	buffer = f_read_from_file(fd);
	close(fd);
	if (!buffer)
	{
		return (false);
	}
	*dest = buffer;
	return (true);
}

static int	f_open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	return (fd);
}

static char	*f_read_from_file(int fd)
{
	t_read	r;

	if (f_init_r(&r) == false)
		return (NULL);
	while (1)
	{
		if (r.position + r.read_size >= r.buffer_size)
		{
			r.buffer = f_resize(&r);
			if (!r.buffer)
				return (printf("Error\nAllocation error."), NULL);
		}
		r.read_bytes = read(fd, &r.buffer[r.position], r.read_size);
		if (r.read_bytes < 0)
			return (free(r.buffer), printf("Read error.\n"), NULL);
		if (r.read_bytes == 0)
			break ;
		r.position += r.read_bytes;
	}
	r.buffer[r.position] = '\0';
	return (r.buffer);
}

static bool	f_init_r(t_read *r)
{
	r->position = 0;
	r->read_size = READ_SIZE;
	r->buffer_size = r->read_size + 1;
	r->buffer = ft_calloc(sizeof(char), r->buffer_size);
	if (!r->buffer)
		return (false);
	return (true);
}
static char	*f_resize(t_read *r)
{
	size_t	size;
	char	*new_buffer;

	r->read_size *= 2;
	size = r->read_size + r->buffer_size;
	new_buffer = ft_calloc(sizeof(char), size);
	if (!new_buffer)
	{
		free(r->buffer);
		return (NULL);
	}
	ft_memcpy(new_buffer, r->buffer, r->position);
	free(r->buffer);
	r->buffer_size = size;
	return (new_buffer);
}
