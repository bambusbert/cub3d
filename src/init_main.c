/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 14:22:57 by slambert          #+#    #+#             */
/*   Updated: 2026/07/17 12:49:02 by slambert         ###   ########.fr       */
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

void	init_god(t_god *god)
{
	debug_init_player(god);
	god->img = mlx_new_image(god->mlx, WSIZE_X, WSIZE_Y);
	if (!god->img)
		error_exit("Error\nerror in init_god\n", god);
	god->img_addr = mlx_get_data_addr(god->img, &god->img_bits_per_pixel,
			&god->img_line_length, &god->img_endian);
	init_angles(god);
	god->pixels_per_x = roundf(WSIZE_X / god->cols);
	god->pixels_per_y = roundf(WSIZE_Y / god->rows);
	god->debug_mode = DEBUG_MODE;
}

// TODO ditch that function if we don't do other stuff in here
void	initialize_map(t_god *p_god)
{
	init_textures(p_god);
}
