/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:35:56 by slambert          #+#    #+#             */
/*   Updated: 2026/07/15 14:36:16 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
