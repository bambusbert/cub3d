/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 14:22:57 by slambert          #+#    #+#             */
/*   Updated: 2026/07/15 14:34:10 by slambert         ###   ########.fr       */
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

void	init_texture_e(t_god *p_god)
{
	p_god->sprite_wall_E->img = mlx_xpm_file_to_image(p_god->mlx, SPRITE_WALL_E,
			&p_god->sprite_wall_E->width, &p_god->sprite_wall_E->height);
	if (!p_god->sprite_wall_E->img)
		error_exit("Error\nerror in init_texture\n", p_god);
	p_god->sprite_wall_E->img_addr = mlx_get_data_addr(p_god->sprite_wall_E->img, &p_god->sprite_wall_E->img_bits_per_pixel,
			&p_god->sprite_wall_E->img_line_length, &p_god->sprite_wall_E->img_endian);
}

void	init_texture_w(t_god *p_god)
{
	p_god->sprite_wall_W->img = mlx_xpm_file_to_image(p_god->mlx, SPRITE_WALL_W,
			&p_god->sprite_wall_W->width, &p_god->sprite_wall_W->height);
	if (!p_god->sprite_wall_W->img)
		error_exit("Error\nerror in init_texture\n", p_god);
	p_god->sprite_wall_W->img_addr = mlx_get_data_addr(p_god->sprite_wall_W->img, &p_god->sprite_wall_W->img_bits_per_pixel,
			&p_god->sprite_wall_W->img_line_length, &p_god->sprite_wall_W->img_endian);
}

void	init_texture_s(t_god *p_god)
{
	p_god->sprite_wall_S->img = mlx_xpm_file_to_image(p_god->mlx, SPRITE_WALL_S,
			&p_god->sprite_wall_S->width, &p_god->sprite_wall_S->height);
	if (!p_god->sprite_wall_S->img)
		error_exit("Error\nerror in init_texture\n", p_god);
	p_god->sprite_wall_S->img_addr = mlx_get_data_addr(p_god->sprite_wall_S->img, &p_god->sprite_wall_S->img_bits_per_pixel,
			&p_god->sprite_wall_S->img_line_length, &p_god->sprite_wall_S->img_endian);
}

void	init_texture_n(t_god *p_god)
{
	p_god->sprite_wall_N->img = mlx_xpm_file_to_image(p_god->mlx, SPRITE_WALL_N,
			&p_god->sprite_wall_N->width, &p_god->sprite_wall_N->height);
	if (!p_god->sprite_wall_N->img)
		error_exit("Error\nerror in init_texture\n", p_god);
	p_god->sprite_wall_N->img_addr = mlx_get_data_addr(p_god->sprite_wall_N->img, &p_god->sprite_wall_N->img_bits_per_pixel,
			&p_god->sprite_wall_N->img_line_length, &p_god->sprite_wall_N->img_endian);
}

void	init_textures(t_god *p_god)
{
	p_god->sprite_wall_E = NULL;
	p_god->sprite_wall_W = NULL;
	p_god->sprite_wall_S = NULL;
	p_god->sprite_wall_N = NULL;
	
	p_god->sprite_wall_E = ft_calloc(sizeof(t_texture), 1);
	if (!p_god->sprite_wall_E)
		error_exit("Error\nerror in initialize_map: wall_E sprite\n", p_god);
	p_god->sprite_wall_W = ft_calloc(sizeof(t_texture), 1);
	if (!p_god->sprite_wall_W)
		error_exit("Error\nerror in initialize_map: wall_W sprite\n", p_god);
	p_god->sprite_wall_S = ft_calloc(sizeof(t_texture), 1);
	if (!p_god->sprite_wall_S)
		error_exit("Error\nerror in initialize_map: wall_S sprite\n", p_god);
	p_god->sprite_wall_N = ft_calloc(sizeof(t_texture), 1);
	if (!p_god->sprite_wall_N)
		error_exit("Error\nerror in initialize_map: wall_N sprite\n", p_god);
	init_texture_n(p_god);
	init_texture_s(p_god);
	init_texture_w(p_god);
	init_texture_e(p_god);
}

void	initialize_map(t_god *p_god)
{
	// maybe other stuff
	init_textures(p_god);
}
