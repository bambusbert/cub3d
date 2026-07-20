/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:03:23 by slambert          #+#    #+#             */
/*   Updated: 2026/07/20 15:20:38 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_god_struct(t_god *god)
{
	unsigned int	i;

	if (!god)
		return ;
	if (!god->map)
	{
		free(god);
		return ;
	}
	i = 0;
	while (i < god->rows && god->map[i])
	{
		free(god->map[i]);
		i++;
	}
	free(god->map);
	god->map = NULL;
	free(god);
}

void	destroy_images(t_god *god)
{
	if (god->img)
		mlx_destroy_image(god->mlx, god->img);
	if (god->sprite_wall_E->img)
		mlx_destroy_image(god->mlx, god->sprite_wall_E->img);
	if (god->sprite_wall_W->img)
		mlx_destroy_image(god->mlx, god->sprite_wall_W->img);
	if (god->sprite_wall_N->img)
		mlx_destroy_image(god->mlx, god->sprite_wall_N->img);
	if (god->sprite_wall_S->img)
		mlx_destroy_image(god->mlx, god->sprite_wall_S->img);
}

static void	perform_cleanup(t_god *god)
{
	if (!god)
		return ;
	destroy_images(god);
	free(god->sprite_wall_E);
	free(god->sprite_wall_W);
	free(god->sprite_wall_S);
	free(god->sprite_wall_N);
	if (god->mlx)
	{
		//mlx_do_key_autorepeaton(god->mlx);
		if (god->mlx_win)
			mlx_destroy_window(god->mlx, god->mlx_win);
		mlx_destroy_display(god->mlx);
		free(god->mlx);
	}
	free_god_struct(god);
}

//TODO eventuell gleich perform_cleanup hooken bei closing event?
void	close_window(t_god *god)
{
	perform_cleanup(god);
	exit(0);
}

void	error_exit(char *msg, t_god *god)
{
	ft_putstr_fd(msg, 2);
	perform_cleanup(god);
	exit(1);
}
