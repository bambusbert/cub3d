/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:35:56 by slambert          #+#    #+#             */
/*   Updated: 2026/07/17 14:14:42 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_texture_e(t_god *god)
{
	god->sprite_wall_E->img = mlx_xpm_file_to_image(god->mlx, SPRITE_WALL_E,
			&god->sprite_wall_E->width, &god->sprite_wall_E->height);
	if (!god->sprite_wall_E->img)
		error_exit("Error\nerror in init_texture\n", god);
	god->sprite_wall_E->img_addr = mlx_get_data_addr(god->sprite_wall_E->img,
			&god->sprite_wall_E->img_bits_per_pixel,
			&god->sprite_wall_E->img_line_length,
			&god->sprite_wall_E->img_endian);
}

void	init_texture_w(t_god *god)
{
	god->sprite_wall_W->img = mlx_xpm_file_to_image(god->mlx, SPRITE_WALL_W,
			&god->sprite_wall_W->width, &god->sprite_wall_W->height);
	if (!god->sprite_wall_W->img)
		error_exit("Error\nerror in init_texture\n", god);
	god->sprite_wall_W->img_addr = mlx_get_data_addr(god->sprite_wall_W->img,
			&god->sprite_wall_W->img_bits_per_pixel,
			&god->sprite_wall_W->img_line_length,
			&god->sprite_wall_W->img_endian);
}

void	init_texture_s(t_god *god)
{
	god->sprite_wall_S->img = mlx_xpm_file_to_image(god->mlx, SPRITE_WALL_S,
			&god->sprite_wall_S->width, &god->sprite_wall_S->height);
	if (!god->sprite_wall_S->img)
		error_exit("Error\nerror in init_texture\n", god);
	god->sprite_wall_S->img_addr = mlx_get_data_addr(god->sprite_wall_S->img,
			&god->sprite_wall_S->img_bits_per_pixel,
			&god->sprite_wall_S->img_line_length,
			&god->sprite_wall_S->img_endian);
}

void	init_texture_n(t_god *god)
{
	god->sprite_wall_N->img = mlx_xpm_file_to_image(god->mlx, SPRITE_WALL_N,
			&god->sprite_wall_N->width, &god->sprite_wall_N->height);
	if (!god->sprite_wall_N->img)
		error_exit("Error\nerror in init_texture\n", god);
	god->sprite_wall_N->img_addr = mlx_get_data_addr(god->sprite_wall_N->img,
			&god->sprite_wall_N->img_bits_per_pixel,
			&god->sprite_wall_N->img_line_length,
			&god->sprite_wall_N->img_endian);
}

void	init_textures(t_god *god)
{
	god->sprite_wall_E = ft_calloc(sizeof(t_texture), 1);
	if (!god->sprite_wall_E)
		error_exit("Error\nerror in initialize_map: wall_E sprite\n", god);
	god->sprite_wall_W = ft_calloc(sizeof(t_texture), 1);
	if (!god->sprite_wall_W)
		error_exit("Error\nerror in initialize_map: wall_W sprite\n", god);
	god->sprite_wall_S = ft_calloc(sizeof(t_texture), 1);
	if (!god->sprite_wall_S)
		error_exit("Error\nerror in initialize_map: wall_S sprite\n", god);
	god->sprite_wall_N = ft_calloc(sizeof(t_texture), 1);
	if (!god->sprite_wall_N)
		error_exit("Error\nerror in initialize_map: wall_N sprite\n", god);
	init_texture_n(god);
	init_texture_s(god);
	init_texture_w(god);
	init_texture_e(god);
}
