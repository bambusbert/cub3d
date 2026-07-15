/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:03:23 by slambert          #+#    #+#             */
/*   Updated: 2026/07/15 15:11:50 by slambert         ###   ########.fr       */
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

void	destroy_images (t_god *god)
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

void free_textures(t_god *god)
{
	free(god->sprite_wall_E);
	free(god->sprite_wall_W);
	free(god->sprite_wall_S);
	free(god->sprite_wall_N);
}

//TODO synchronize close_window and error_exit
int	close_window(t_god	*god)
{
	//destroy_sprites(god);
	destroy_images(god);
	free_textures(god);
	if (god->mlx_win)
		mlx_destroy_window(god->mlx, god->mlx_win);
	if (god->mlx)
	{
		mlx_do_key_autorepeaton(god->mlx);
		mlx_destroy_display(god->mlx);
		free(god->mlx);
	}
	// if (god->count_collectible == 0)
	// 	ft_printf("Moves: %u\n", map->moves + 1);
	free_god_struct(god);
	
	exit(0);
}

void	error_exit(char *msg, t_god *p_god)
{
	ft_putstr_fd(msg, 2);
	if (p_god->mlx)
	{
		//destroy_sprites(p_god);
		destroy_images(p_god);
		free_textures(p_god);
		if (p_god->mlx_win)
			mlx_destroy_window(p_god->mlx, p_god->mlx_win);
		mlx_destroy_display(p_god->mlx);
		free(p_god->mlx);
	}
	free_god_struct(p_god);
	exit(1);
}
