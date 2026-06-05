/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:03:23 by slambert          #+#    #+#             */
/*   Updated: 2026/06/05 15:41:36 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	close_window(t_god *god)
{
	destroy_sprites(god);
	if (god->mlx_win)
		mlx_destroy_window(god->mlx, god->mlx_win);
	if (god->mlx)
	{
		mlx_destroy_display(god->mlx);
		free(god->mlx);
	}
	// if (god->count_collectible == 0)
	// 	ft_printf("Moves: %u\n", map->moves + 1);
	free_god_struct(god);
	exit(0);
}

void	destroy_sprites(t_god *p_god)
{
	if (p_god->sprite_player)
		mlx_destroy_image(p_god->mlx, p_god->sprite_player);
	if (p_god->sprite_wall_S)
		mlx_destroy_image(p_god->mlx, p_god->sprite_wall_S);
	if (p_god->sprite_wall_N)
		mlx_destroy_image(p_god->mlx, p_god->sprite_wall_N);
	if (p_god->sprite_wall_E)
		mlx_destroy_image(p_god->mlx, p_god->sprite_wall_E);
	if (p_god->sprite_wall_W)
		mlx_destroy_image(p_god->mlx, p_god->sprite_wall_W);
	p_god->sprite_player = NULL;
	p_god->sprite_wall_S = NULL;
	p_god->sprite_wall_N = NULL;
	p_god->sprite_wall_E = NULL;
	p_god->sprite_wall_W = NULL;
}

void	error_exit(char *msg, t_god *p_god)
{
	ft_putstr_fd(msg, 2);
	if (p_god->mlx)
	{
		destroy_sprites(p_god);
		if (p_god->mlx_win)
			mlx_destroy_window(p_god->mlx, p_god->mlx_win);
		mlx_destroy_display(p_god->mlx);
		free(p_god->mlx);
	}
	free_god_struct(p_god);
	exit(-1);
}