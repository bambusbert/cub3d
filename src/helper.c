/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 14:58:18 by slambert          #+#    #+#             */
/*   Updated: 2026/07/17 16:37:38 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_wall_coord(t_god *god, float x, float y)
{
	int	x_int;
	int	y_int;

	x_int = (int)x / god->pixels_per_x;
	y_int = (int)y / god->pixels_per_y;
	if (x_int > (int)god->cols - 1 || y_int > (int)god->rows - 1 || x_int < 0
		|| y_int < 0)
		return (1);
	if (god->map[y_int][x_int] == 1)
		return (1);
	return (0);
}

int	normalize_coordinate(t_god *god, float coord, int type)
{
	if (type == XCOORD)
		return (coord * god->pixels_per_x);
	else if (type == YCOORD)
		return (coord * god->pixels_per_y);
	else
		return (-666);
}

// possible TODO change into normalize_angles function that handles all 
//3 angle variables at once so we do not have 3 calls in update_player_angle
void	normalize_angle(float *angle)
{
	if (*angle > 2 * PI)
		*angle -= 2 * PI;
	else if (*angle < 0)
		*angle += 2 * PI;
}

// TODO this will be bonus
// TODO bug where the outermost beams sometimes are not displayed completely.
//		i think this has to do smth with the division by MINIMAP_FACTOR
// TODO atm the whole beam is drawn. it would be better to only have a
//		defined length for each beam
void	visualize_2d_beam(t_god *god, t_dda *dda)
{
	static int	draw;
	int			start_pixel_x;
	int			start_pixel_y;
	int			end_pixel_x;
	int			end_pixel_y;

	dda->hit_x = god->player_x + (dda->ray_dir_x * dda->beam_dist);
	dda->hit_y = god->player_y + (dda->ray_dir_y * dda->beam_dist);
	start_pixel_x = god->player_x * god->pixels_per_x;
	start_pixel_y = god->player_y * god->pixels_per_y;
	end_pixel_x = dda->hit_x * god->pixels_per_x;
	end_pixel_y = dda->hit_y * god->pixels_per_y;
	if (draw % MINIMAP_BEAMS_DRAWN == 0)
		ft_draw_line(god, (t_ipoint){start_pixel_x / MINIMAP_FACTOR, start_pixel_y / MINIMAP_FACTOR},
			(t_ipoint){end_pixel_x / MINIMAP_FACTOR, end_pixel_y / MINIMAP_FACTOR},
			COLOR_WHITE);
	draw++;
}
