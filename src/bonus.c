/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 15:08:20 by slambert          #+#    #+#             */
/*   Updated: 2026/08/26 14:05:56 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	mouse_move_function(int x, int y, void *param)
{
	static int	count = 0;
	t_god		*god;

	(void)y;
	if (count++ < 13)
		return (0);
	god = (t_god *)param;
	if (x > WSIZE_X / 2)
	{
		update_player_angle(god, RIGHT);
		mlx_mouse_move(god->mlx, god->mlx_win, WSIZE_X / 2, WSIZE_Y / 2);
	}
	else if (x < WSIZE_X / 2)
	{
		update_player_angle(god, LEFT);
		mlx_mouse_move(god->mlx, god->mlx_win, WSIZE_X / 2, WSIZE_Y / 2);
	}
	count = 0;
	return (0);
}

static void	draw_minimap_beam(t_god *god, float angle)
{
	int	start_pixel_x;
	int	start_pixel_y;
	int	end_pixel_x;
	int	end_pixel_y;

	start_pixel_x = god->player_x * god->pixels_per_x;
	start_pixel_y = god->player_y * god->pixels_per_y;
	end_pixel_x = start_pixel_x + cos(angle) * MINIMAP_BEAM_L;
	end_pixel_y = start_pixel_y + sin(angle) * MINIMAP_BEAM_L;
	ft_draw_line(god, (t_ipoint){start_pixel_x / MINIMAP_FACTOR, start_pixel_y
		/ MINIMAP_FACTOR}, (t_ipoint){end_pixel_x / MINIMAP_FACTOR, end_pixel_y
		/ MINIMAP_FACTOR}, COLOR_WHITE);
}

// possible TODO 2 additional angles between
void	draw_minimap_beams(t_god *god)
{
	draw_minimap_beam(god, god->player_angle_min);
	draw_minimap_beam(god, god->player_angle - ANGLE_OFFSET / 2);
	draw_minimap_beam(god, god->player_angle);
	draw_minimap_beam(god, god->player_angle + ANGLE_OFFSET / 2);
	draw_minimap_beam(god, god->player_angle_max);
}
