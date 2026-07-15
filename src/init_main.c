/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 14:22:57 by slambert          #+#    #+#             */
/*   Updated: 2026/07/15 14:36:20 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_angles(t_god *god)
{
	if (god->player_start_direction == NORTH)
		god->player_angle = 3 * PI / 2;
	else if (god->player_start_direction == EAST)
		god->player_angle = 0;
	else if (god->player_start_direction == SOUTH)
		god->player_angle = PI / 2;
	else if (god->player_start_direction == WEST)
		god->player_angle = PI;
	god->player_angle_min = god->player_angle - ANGLE_OFFSET;
	normalize_angle(&god->player_angle_min);
	god->player_angle_max = god->player_angle + ANGLE_OFFSET;
	normalize_angle(&god->player_angle_max);
}

// TODO initialize every pointer with NULL
void	init_god(t_god *god)
{
	debug_init_player(god);
	god->img = mlx_new_image(god->mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y);
	if (!god->img)
		error_exit("Error\nerror in init_god\n", god);
	god->img_addr = mlx_get_data_addr(god->img, &god->img_bits_per_pixel,
			&god->img_line_length, &god->img_endian);
	// TODO error protection?
	init_angles(god);
	// TODO think if there can be a case where i would draw out of scope
	//(i think theoretically it could happen BUT i use safeguards every
	// time i put pixels)
	god->pixels_per_x = roundf(WINDOW_SIZE_X / god->cols);
	god->pixels_per_y = roundf(WINDOW_SIZE_Y / god->rows);
	god->key_a = false;
	god->key_s = false;
	god->key_d = false;
	god->key_w = false;
	god->key_left = false;
	god->key_right = false;
	god->debug_mode = DEBUG_MODE;
}

void	initialize_map(t_god *p_god)
{
	// maybe other stuff
	init_textures(p_god);
}
