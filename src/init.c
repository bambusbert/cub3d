/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 14:22:57 by slambert          #+#    #+#             */
/*   Updated: 2026/06/24 14:48:06 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    init_angles(t_god *god)
{
    //player_angle is initially 0 (NORTH)
	god->player_angle = 0;
    //initially 0.5f so the funnel is 2*0.5=1rad wide
    god->angle_offset = ANGLE_OFFSET;
    god->player_angle_min = god->player_angle - god->angle_offset;
    normalize_angle(&god->player_angle_min);
    god->player_angle_max = god->player_angle + god->angle_offset;
    normalize_angle(&god->player_angle_max);
    //god->angle_tick = ANGLE_FRACTION;   //equals 1 degree
}

//TODO initialize every pointer with NULL
void	init_stuff(t_god *god)
{
	// we should do something like:
	// int player_pos[2];

	// player_pos = get_player_position (god);
	// god->player_x = player_pos[0];
	// god->player_y = player_pos[1];

	//3/4 is a placeholder, that's the position of the player in the sample map
	god->player_x = 3;
	god->player_y = 4;
	god->img = mlx_new_image(god->mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y);
	//TODO error protection
	god->img_addr = mlx_get_data_addr(god->img, &god->img_bits_per_pixel, &god->img_line_length,
								&god->img_endian);
	//TODO error protection?
	init_angles(god);
	god->pixels_per_x = roundf(WINDOW_SIZE_X / god->cols);
	god->pixels_per_y = roundf(WINDOW_SIZE_Y / god->rows);
	god->key_a = false;
	god->key_s = false;
	god->key_d = false;
	god->key_w = false;
	god->key_left = false;
	god->key_right = false;
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