/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 14:22:57 by slambert          #+#    #+#             */
/*   Updated: 2026/07/02 14:24:14 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    init_angles(t_god *god)
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

//TODO initialize every pointer with NULL
void	init_god(t_god *god)
{

	debug_init_player(god);
	god->img = mlx_new_image(god->mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y);
	//TODO error protection
	god->img_addr = mlx_get_data_addr(god->img, &god->img_bits_per_pixel, &god->img_line_length,
								&god->img_endian);
	//TODO error protection?
	init_angles(god);
	//TODO think if there can be a case where i would draw out of scope
	//(i think theoretically it could happen BUT i use safeguards every
	//time i put pixels)
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
	int	w;
	int	h;

	p_god->sprite_player = mlx_xpm_file_to_image(p_god->mlx, SPRITE_PLAYER, &w, &h);
	if (!p_god->sprite_player)
		error_exit("Error\nerror in initialize_map: player sprite\n", p_god);
	p_god->sprite_wall_E = mlx_xpm_file_to_image(p_god->mlx,
			SPRITE_WALL_E, &w, &h);
	if (!p_god->sprite_wall_E)
		error_exit("Error\nerror in initialize_map: wall_E sprite\n", p_god);
	p_god->sprite_wall_N = mlx_xpm_file_to_image(p_god->mlx, SPRITE_WALL_N, &w, &h);
	if (!p_god->sprite_wall_N)
		error_exit("Error\nerror in initialize_map: wall_N sprite\n", p_god);
	p_god->sprite_wall_S = mlx_xpm_file_to_image(p_god->mlx, SPRITE_WALL_S, &w, &h);
	if (!p_god->sprite_wall_S)
		error_exit("Error\nerror in initialize_map: wall_S sprite\n", p_god);
	p_god->sprite_wall_W = mlx_xpm_file_to_image(p_god->mlx, SPRITE_WALL_W, &w, &h);
	if (!p_god->sprite_wall_W)
		error_exit("Error\nerror in initialize_map: wall_W sprite\n", p_god);
}