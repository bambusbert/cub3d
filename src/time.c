/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 14:44:54 by slambert          #+#    #+#             */
/*   Updated: 2026/08/22 11:52:04 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

long long	return_usecs_since_1970(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

// long long is 64 bits on all OSes >=64bit
//(long is 32bit on 32bit OS, that would be too little)
void	update_time_since_last_frame(t_god *god)
{
	long long	cur_time_usec;

	cur_time_usec = return_usecs_since_1970();
	if (cur_time_usec == -1)
		error_exit("Error\ngettimeofday failed\n", god);
	if (god->time_since_last_frame_sec == 0)
		god->time_since_last_frame_sec = 0.0075;
	else
		god->time_since_last_frame_sec = (float)(cur_time_usec
				- god->time_last_frame_usec) / 1000000;
	god->time_last_frame_usec = cur_time_usec;
}
