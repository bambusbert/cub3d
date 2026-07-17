/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:35:56 by slambert          #+#    #+#             */
/*   Updated: 2026/07/17 14:43:32 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_texture(t_god *god, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(god->mlx, path, &tex->width, &tex->height);
	if (!(tex->img))
		error_exit("Error\nerror in init_texture\n", god);
	tex->img_addr = mlx_get_data_addr(tex->img, &tex->img_bits_per_pixel,
			&tex->img_line_length, &tex->img_endian);
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
	init_texture(god, god->sprite_wall_N, SPRITE_WALL_N);
	init_texture(god, god->sprite_wall_E, SPRITE_WALL_E);
	init_texture(god, god->sprite_wall_S, SPRITE_WALL_S);
	init_texture(god, god->sprite_wall_W, SPRITE_WALL_W);
}
