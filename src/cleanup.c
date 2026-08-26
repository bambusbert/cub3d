/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:03:23 by slambert          #+#    #+#             */
/*   Updated: 2026/08/26 14:13:36 by slambert         ###   ########.fr       */
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
	if (!god)
		return ;
	if (god->god_tex && god->god_tex->img && god->mlx)
		mlx_destroy_image(god->mlx, god->god_tex->img);
	if (god->sprite_wall_e && god->sprite_wall_e->img && god->mlx)
		mlx_destroy_image(god->mlx, god->sprite_wall_e->img);
	if (god->sprite_wall_w && god->sprite_wall_w->img && god->mlx)
		mlx_destroy_image(god->mlx, god->sprite_wall_w->img);
	if (god->sprite_wall_n && god->sprite_wall_n->img && god->mlx)
		mlx_destroy_image(god->mlx, god->sprite_wall_n->img);
	if (god->sprite_wall_s && god->sprite_wall_s->img && god->mlx)
		mlx_destroy_image(god->mlx, god->sprite_wall_s->img);
}

static void	perform_cleanup(t_god *god)
{
	if (!god)
		return ;
	free_db(god->db);
	destroy_images(god);
	free(god->sprite_wall_e);
	free(god->sprite_wall_w);
	free(god->sprite_wall_s);
	free(god->sprite_wall_n);
	if (god->mlx)
	{
		if (god->mlx_win)
			mlx_destroy_window(god->mlx, god->mlx_win);
		mlx_destroy_display(god->mlx);
		free(god->mlx);
	}
	free(god->god_tex);
	free_god_struct(god);
}

int	close_window(t_god *god)
{
	perform_cleanup(god);
	exit(0);
	return (0);
}

void	error_exit(char *msg, t_god *god)
{
	ft_putstr_fd(msg, 2);
	perform_cleanup(god);
	exit(1);
}
