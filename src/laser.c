/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 14:58:18 by slambert          #+#    #+#             */
/*   Updated: 2026/06/24 14:21:32 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// we don't need that anymore
// int is_grid_coord(t_god *god, float x, float y)
// {
// 	if ((int)roundf(x) % god->pixels_per_x == 0)
// 		return (1);
// 	if ((int)roundf(y) % god->pixels_per_y == 0)
// 		return (1);
// 	return (0);
// }

int	is_wall_coord(t_god *god, float x, float y)
{
	int	x_int;
	int	y_int;

	x_int = (int)x / god->pixels_per_x;
	y_int = (int)y / god->pixels_per_y;
	if (x_int > god->cols - 1 || y_int > god->rows - 1 || x_int < 0
		|| y_int < 0)
		return (1);
	if (god->map[y_int][x_int] == 1)
		return (1);
	return (0);
}

/*	1.	calculate dx and dy. these distances are the x any y values the line to
 *		be drawn travels (line = hypothenuse, dx and dy kathete).
 *	2.	calculate the step. this is the max of the absolute values of dx and dy.
 *	3.	calculate dx and dy PER STEP - divide by step.
 *		(start from point 1)
 *	4.	loop from i to step and increment by the values from 3.
 *		round to nearest pixel.
 */
void	ft_draw_line(t_god *god, int x1, int y1, int x2, int y2, int color)
{
	float	step;
	float	x;
	float	y;
	float	delta_x;
	float	delta_y;
	int		i;

	delta_x = (x2 - x1);
	delta_y = y2 - y1;
	if (abs((int)delta_x) >= abs((int)delta_y))
		step = abs((int)delta_x);
	else
		step = abs((int)delta_y);
	delta_x = delta_x / step;
	delta_y = delta_y / step;
	x = x1;
	y = y1;
	i = -1;
	while (++i <= step)
	{
		// if (is_wall_coord(god, x, y))
		// 	break ;
		my_mlx_pixel_put(god, (int)round(x), (int)round(y), color);
		x += delta_x;
		y += delta_y;
	}
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

/* void	draw_beam_from_player_inefficient(t_god *god, float beam_angle)
{
	float	start_x;
	float	start_y;
	float	end_x;
	float	end_y;
	int		len;

	len = 200;
	start_x = (god->player_x * god->pixels_per_x) + (god->pixels_per_x / 2);
	start_y = (god->player_y * god->pixels_per_y) + (god->pixels_per_y / 2);
	end_x = start_x + (len * cos(beam_angle));
	end_y = start_y + (len * sin(beam_angle));
	ft_draw_line(god, (int)start_x, (int)start_y, (int)end_x, (int)end_y,
		COLOR_ORANGE);
} */

void	my_mlx_pixel_put(t_god *god, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_SIZE_X || y < 0 || y >= WINDOW_SIZE_Y)
		return ;
	dst = god->img_addr + (y * god->img_line_length + x
			* (god->img_bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
