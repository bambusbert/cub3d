/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 14:18:12 by slambert          #+#    #+#             */
/*   Updated: 2026/07/01 13:40:59 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 *	it would be very inefficient if we just drew pixel by pixel.
 *	a wall can only be at the grid lines (not inbetween).
 *	therefore, it is enough to check whether the next grid line
 *	that is reached by the beam is the next horizontal or
 *	vertical grid line. we can draw this line. after that we
 *	check if the regarding block is a wall or not. if it is,
 *	stop and calculate the total beam distance (i guess we need
 *	an array of size WINDOW_SIZE_X for that?)
 *
 * the DDA algo is split into 2 phases.
 * Phase 1: set up all the variables needed.
 * 			- x / y position of the player (int)
 * 			- step_x / step_y:	binary information regarding the
 * 								the player angle (1 or -1)
 * 			- delta_x:	length of a vector that passes from one
 * 						vertical line to another
 * 			- delta_y:	length of a vector that passes from one
 * 						horizontal line to another
 * 			- next_x:	length of the vector that passes from the
 * 						player to the first vertical line
 * 			- next_y:	length of the vector that passes from the
 * 						player to the first horizontal line
 *
 * Phase 2: the actual while loop. while no wall has been hit,
 * 			we add the distance to the nearest grid line to the
 * 			total distance. if the next block is a wall, we stop.
 * 			if not, we continue. if we hit a wall, save distance
 * 			and draw the line.
 */
#include "cub3d.h"

void	dda_loop(t_god *god, t_dda *dda)
{
	while (!dda->wall_hit)
	{
		if (dda->next_x < dda->next_y)
		{
			dda->next_x += dda->delta_x;
			dda->map_x += dda->step_x;
			dda->which_wall_hit = true;
		}
		else
		{
			dda->next_y += dda->delta_y;
			dda->map_y += dda->step_y;
			dda->which_wall_hit = false;
		}
		// boundary check
		if (dda->map_x < 0 || dda->map_x >= (int)god->cols || dda->map_y < 0
			|| dda->map_y >= (int)god->rows)
		{
			dda->wall_hit = true;
			break ;
		}
		// collision check
		if (god->map[dda->map_y][dda->map_x] == 1)
			dda->wall_hit = true;
	}
}

void	calc_distances(float angle_diff, t_dda *dda)
{
	if (dda->which_wall_hit)
	{
		if (dda->ray_dir_x == 0)
            dda->ray_dir_x = 0.0000001;
		dda->wall_dist = (dda->next_x - dda->delta_x) * cos(angle_diff);
		dda->beam_dist = dda->next_x - dda->delta_x;
    }
	else
	{
		if (dda->ray_dir_y == 0)
            dda->ray_dir_y = 0.0000001;
		dda->wall_dist = (dda->next_y - dda->delta_y) * cos(angle_diff);
		dda->beam_dist = dda->next_y - dda->delta_y;
    }
    if (dda->wall_dist < 0.0001)
	{
    	dda->wall_dist = 0.0001;
	}
	if (dda->beam_dist < 0.0001)
    {
		dda->beam_dist = 0.0001;
	}	
}

//dPerp = dEuclidian * cos(ray_angle - player_angle)
void	dda_single_ray(t_god *god, float beam_angle, int x)
{
	t_dda	dda;
	int		line_len;
	float	angle_diff;

	init_dda_struct(&dda, god, beam_angle);
	dda_loop(god, &dda);
	angle_diff = beam_angle - god->player_angle;
	calc_distances(angle_diff, &dda);
	line_len = WINDOW_SIZE_Y / dda.wall_dist;
	if(!god->debug_mode)
		draw_vertical(god, &dda, line_len, x);
	if (god->debug_mode)
		visualize_2d_beam(god, &dda);
}

void	dda_wrapper(t_god *god)
{
	float	angle_to_draw;
	float	angle_step;
	int		x;

	// Divide the total FOV by the screen width to get the angle per pixel column
	angle_step = god->angle_offset * 2 / WINDOW_SIZE_X;
	angle_to_draw = god->player_angle_min;
	x = -1;
	while (++x < WINDOW_SIZE_X)
	{
		normalize_angle(&angle_to_draw);
		dda_single_ray(god, angle_to_draw, x);
		angle_to_draw += angle_step;
	}
}
