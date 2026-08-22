/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 14:22:57 by slambert          #+#    #+#             */
/*   Updated: 2026/08/22 11:51:03 by slambert         ###   ########.fr       */
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
	god->god_tex = ft_calloc(sizeof(t_texture), 1);
	if (!god->god_tex)
		error_exit("Error\nmalloc error\n", god);
	god->god_tex->img = mlx_new_image(god->mlx, WSIZE_X, WSIZE_Y);
	if (!god->god_tex->img)
		error_exit("Error\nerror in init_god\n", god);
	god->god_tex->img_addr = mlx_get_data_addr(god->god_tex->img,
			&god->god_tex->img_bpp, &god->god_tex->img_ll,
			&god->god_tex->img_endian);
	init_angles(god);
	god->pixels_per_x = roundf(WSIZE_X / (god->cols));
	god->pixels_per_y = roundf(WSIZE_Y / (god->rows));
}
