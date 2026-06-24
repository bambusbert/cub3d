/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 15:46:53 by slambert          #+#    #+#             */
/*   Updated: 2026/06/24 14:28:52 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//possible TODO change into normalize_angles function that handles
//all 3 angle variables at once so we do not have 3 calls in update_player_angle
void normalize_angle (float *angle)
{
	if (*angle > 2 * PI)
		*angle -= 2 * PI;
	else if (*angle < 0)
		*angle += 2 * PI;
}

void draw_square (t_god* god, int row, int col, int pixels_x, int pixels_y)
{
	int cur_x;
	int cur_y;
	int start_x;
	int start_y;
	int color;
	
	start_x = col * pixels_x;
	start_y = row * pixels_y;
	cur_x = -1;
	while (++cur_x < pixels_x)
	{
		cur_y = -1;
		while (++cur_y < pixels_y)
		{
			my_mlx_pixel_put(god, cur_x + start_x, cur_y + start_y, COLOR_BLUE);
			// mlx_pixel_put(god->mlx, god->mlx_win, cur_x + start_x, cur_y + start_y, color);
		}
	}
}

//atm only possible to draw recangular maps.
//TODO change that
void draw_2d_map(t_god* god)
{
	int i;
	int j;

	i = -1;
	while (++i < god->rows)
	{
		j = -1;
		while (++j < god->cols)
		{
			if (god->map[i][j] == 1)
				draw_square(god, i, j, god->pixels_per_x, god->pixels_per_y);
		}
	}
}
