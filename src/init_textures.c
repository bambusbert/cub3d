/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:35:56 by slambert          #+#    #+#             */
/*   Updated: 2026/08/25 14:11:06 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_texture(t_god *god, t_texture *tex, const char *path)
{
	tex->img = mlx_xpm_file_to_image(god->mlx, (char *)path, &tex->width,
			&tex->height);
	if (!(tex->img))
		error_exit("Error\nerror in init_texture\n", god);
	tex->img_addr = mlx_get_data_addr(tex->img, &tex->img_bpp, &tex->img_ll,
			&tex->img_endian);
}

void	init_textures(t_god *god)
{
	god->sprite_wall_e = ft_calloc(sizeof(t_texture), 1);
	if (!god->sprite_wall_e)
		error_exit("Error\nerror in initialize_map: wall_E sprite\n", god);
	god->sprite_wall_w = ft_calloc(sizeof(t_texture), 1);
	if (!god->sprite_wall_w)
		error_exit("Error\nerror in initialize_map: wall_W sprite\n", god);
	god->sprite_wall_s = ft_calloc(sizeof(t_texture), 1);
	if (!god->sprite_wall_s)
		error_exit("Error\nerror in initialize_map: wall_S sprite\n", god);
	god->sprite_wall_n = ft_calloc(sizeof(t_texture), 1);
	if (!god->sprite_wall_n)
		error_exit("Error\nerror in initialize_map: wall_N sprite\n", god);
	init_texture(god, god->sprite_wall_n, god->path_wall_n);
	init_texture(god, god->sprite_wall_e, god->path_wall_e);
	init_texture(god, god->sprite_wall_s, god->path_wall_s);
	init_texture(god, god->sprite_wall_w, god->path_wall_w);
}
