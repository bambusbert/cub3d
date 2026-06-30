/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 14:18:12 by slambert          #+#    #+#             */
/*   Updated: 2026/06/30 17:06:12 by slambert         ###   ########.fr       */
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
		if (dda->map_x < 0 || dda->map_x >= god->cols || dda->map_y < 0
			|| dda->map_y >= god->rows)
		{
			dda->wall_hit = true;
			break ;
		}
		// collision check
		if (god->map[dda->map_y][dda->map_x] == 1)
			dda->wall_hit = true;
	}
}

void	init_dda_step_and_next(t_god *god, t_dda *dda)
{
	if (dda->ray_dir_x < 0)
	{
		dda->step_x = -1; // Looking Left
		dda->next_x = (god->player_x - dda->player_x_int) * dda->delta_x;
	}
	else
	{
		dda->step_x = 1; // Looking Right
		dda->next_x = (dda->player_x_int + 1.0 - god->player_x) * dda->delta_x;
	}
	if (dda->ray_dir_y < 0)
	{
		dda->step_y = -1; // Looking Up
		dda->next_y = (god->player_y - dda->player_y_int) * dda->delta_y;
	}
	else
	{
		dda->step_y = 1; // Looking Down
		dda->next_y = (dda->player_y_int + 1.0 - god->player_y) * dda->delta_y;
	}
}

void init_dda_struct(t_dda *dda, t_god *god, float beam_angle)
{
	dda->ray_dir_x = cos(beam_angle);
	dda->ray_dir_y = sin(beam_angle);
	dda->player_x_int = (int)god->player_x;
	dda->player_y_int = (int)god->player_y;
	dda->delta_x = fabs(1.0 / dda->ray_dir_x);
	dda->delta_y = fabs(1.0 / dda->ray_dir_y);
	init_dda_step_and_next(god, dda);
	dda->wall_hit = false;
	dda->map_x = dda->player_x_int;
	dda->map_y = dda->player_y_int;
}

void	visualize_2d_beam(t_god *god, t_dda *dda)
{
	float	hit_x;
	float	hit_y;
	int		start_pixel_x;
	int		start_pixel_y;
	int		end_pixel_x;
	int		end_pixel_y;

	hit_x = god->player_x + (dda->ray_dir_x * dda->dist);
	hit_y = god->player_y + (dda->ray_dir_y * dda->dist);
	start_pixel_x = god->player_x * god->pixels_per_x;
	start_pixel_y = god->player_y * god->pixels_per_y;
	end_pixel_x = hit_x * god->pixels_per_x;
	end_pixel_y = hit_y * god->pixels_per_y;
	ft_draw_line(god, start_pixel_x, start_pixel_y, end_pixel_x, end_pixel_y,
		COLOR_ORANGE);
}

void	calc_perpendicular_dist(t_god *god, float angle_diff, t_dda *dda)
{
	if (dda->which_wall_hit)
	{
		if (dda->ray_dir_x == 0)
            dda->ray_dir_x = 0.0000001;
		dda->dist = (dda->next_x - dda->delta_x) * cos(angle_diff);
    }
	else
	{
		if (dda->ray_dir_y == 0)
            dda->ray_dir_y = 0.0000001;
		dda->dist = (dda->next_y - dda->delta_y) * cos(angle_diff);
    }
    if (dda->dist < 0.0001)
        dda->dist = 0.0001;
}

//draws the vertical slice
void draw_candle(t_god *god, t_dda* dda, float wall_len, int x)
{
	int draw_start;
	int draw_end;
	int middle;

	middle = WINDOW_SIZE_Y / 2;
	draw_start = middle - wall_len / 2;
	draw_end = middle + wall_len / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WINDOW_SIZE_Y)
		draw_end = WINDOW_SIZE_Y - 1;
	if (draw_start < 0 || draw_start > WINDOW_SIZE_Y)
		draw_start = 0;
	if (draw_end >= WINDOW_SIZE_Y || draw_end < 0)
		draw_end = WINDOW_SIZE_Y - 1;
	ft_draw_line(god, x, 0, x, draw_start - 1, COLOR_CEILING);
	ft_draw_line(god, x, draw_start, x, draw_end, COLOR_WALL);
	ft_draw_line(god, x, draw_end + 1, x, WINDOW_SIZE_Y, COLOR_FLOOR);
}

//dPerp = dEuclidian * cos(theta_ray - theta_player)
void	dda_single_ray(t_god *god, float beam_angle, int x)
{
	t_dda	dda;
	int		line_len;
	float	angle_diff;

	init_dda_struct(&dda, god, beam_angle);
	dda_loop(god, &dda);
	angle_diff = beam_angle - god->player_angle;
	calc_perpendicular_dist(god, angle_diff, &dda);
	line_len = WINDOW_SIZE_Y / dda.dist;
	if(!DEBUG_MODE)
		draw_candle(god, &dda, line_len, x);
	if (DEBUG_MODE)
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
