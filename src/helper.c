/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 14:58:18 by slambert          #+#    #+#             */
/*   Updated: 2026/07/21 13:56:15 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_wall_coord(t_god *god, float x, float y)
{
	int	x_int;
	int	y_int;

	x_int = (int)x / god->pixels_per_x;
	y_int = (int)y / god->pixels_per_y;
	if (x_int > (int)god->cols - 1 || y_int > (int)god->rows - 1 || x_int < 0
		|| y_int < 0)
		return (1);
	if (god->map[y_int][x_int] == 1)
		return (1);
	return (0);
}

int	normalize_coordinate(t_god *god, float coord, int type)
{
	if (type == XCOORD)
		return (coord * god->pixels_per_x);
	else if (type == YCOORD)
		return (coord * god->pixels_per_y);
	else
		return (-666);
}

void	normalize_angle(float *angle)
{
	if (*angle > 2 * PI)
		*angle -= 2 * PI;
	else if (*angle < 0)
		*angle += 2 * PI;
}
