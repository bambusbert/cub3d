/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 14:18:12 by slambert          #+#    #+#             */
/*   Updated: 2026/06/24 14:20:41 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_dda	*init_dda_struct(t_god *god, float beam_angle)
{
	t_dda	*dda;

	dda = ft_calloc(sizeof(t_dda), 1);
	if (!dda)
		error_exit("malloc failure in init_dda\n", god);
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
	return (dda);
}

void visualize_beam(t_god *god, t_dda *dda)
{
    float	hit_x;
	float	hit_y;
	int		start_pixel_x;
	int		start_pixel_y;
	int		end_pixel_x;
	int		end_pixel_y;
    
    hit_x = god->player_x + (dda->ray_dir_x * dda->distance);
	hit_y = god->player_y + (dda->ray_dir_y * dda->distance);
	start_pixel_x = god->player_x * god->pixels_per_x;
	start_pixel_y = god->player_y * god->pixels_per_y;
	end_pixel_x = hit_x * god->pixels_per_x;
	end_pixel_y = hit_y * god->pixels_per_y;
	ft_draw_line(god, start_pixel_x, start_pixel_y, end_pixel_x, end_pixel_y,
		COLOR_ORANGE);
}

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
// TODO understand DDA better and put these variables in a struct
// TODO rename to dda
void	dda_wrapper(t_god *god, float beam_angle)
{
	t_dda	*dda;

	dda = init_dda_struct(god, beam_angle);
	dda_loop(god, dda);
	// for debugging (and minimap) we draw the 2d rays
	if (dda->which_wall_hit)
		dda->distance = (dda->map_x - god->player_x + (1 - dda->step_x) / 2)/ dda->ray_dir_x;
	else
		dda->distance = (dda->map_y - god->player_y + (1 - dda->step_y) / 2)/ dda->ray_dir_y;
	//TODO calculate the line length which is WINDOWS_SIZE_Y / distance
    
    //TODOvisualize line length
    
    //for Debug (and minimap later) visualize it
    visualize_beam(god, dda);
}
