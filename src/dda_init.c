/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 12:45:32 by slambert          #+#    #+#             */
/*   Updated: 2026/07/21 12:25:24 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_dda_step_and_next(t_god *god, t_dda *dda)
{
	if (dda->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->next_x = (god->player_x - dda->player_x_int) * dda->delta_x;
	}
	else
	{
		dda->step_x = 1;
		dda->next_x = (dda->player_x_int + 1.0 - god->player_x) * dda->delta_x;
	}
	if (dda->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->next_y = (god->player_y - dda->player_y_int) * dda->delta_y;
	}
	else
	{
		dda->step_y = 1;
		dda->next_y = (dda->player_y_int + 1.0 - god->player_y) * dda->delta_y;
	}
}

void	init_dda_struct(t_dda *dda, t_god *god, float beam_angle)
{
	dda->ray_dir_x = cos(beam_angle);
	dda->ray_dir_y = sin(beam_angle);
	dda->player_x_int = (int)god->player_x;
	dda->player_y_int = (int)god->player_y;
	dda->delta_x = fabs(1.0 / dda->ray_dir_x);
	dda->delta_y = fabs(1.0 / dda->ray_dir_y);
	init_dda_step_and_next(god, dda);
	dda->wall_hit = false;
	dda->horizontal_wall_hit = false;
	dda->map_x = dda->player_x_int;
	dda->map_y = dda->player_y_int;
	dda->which_wall_hit = -1;
}
