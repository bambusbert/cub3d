/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 15:46:53 by slambert          #+#    #+#             */
/*   Updated: 2026/07/01 12:49:26 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	my_mlx_pixel_put(t_god *god, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_SIZE_X || y < 0 || y >= WINDOW_SIZE_Y)
		return ;
	dst = god->img_addr + (y * god->img_line_length + x
			* (god->img_bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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
		my_mlx_pixel_put(god, (int)round(x), (int)round(y), color);
		x += delta_x;
		y += delta_y;
	}
}

void draw_square (t_god* god, int row, int col, int pixels_x, int pixels_y)
{
	int cur_x;
	int cur_y;
	int start_x;
	int start_y;
	//int color;
	
	start_x = col * pixels_x;
	start_y = row * pixels_y;
	cur_x = -1;
	while (++cur_x < pixels_x)
	{
		cur_y = -1;
		while (++cur_y < pixels_y)
		{
			my_mlx_pixel_put(god, cur_x + start_x, cur_y + start_y, COLOR_BLUE);
			// mlx_pixel_put(god->mlx, god->mlx_win, cur_x + start_x, cur_y + start_y, color);
		}
	}
}

//atm only possible to draw recangular maps.
//TODO change that
//or not - a non rectangular map is also rectangular when we just fill the
//space in between
void draw_2d_map(t_god* god)
{
	int i;
	int j;

	i = -1;
	while (++i < (int)god->rows)
	{
		j = -1;
		while (++j < (int)god->cols)
		{
			if (god->map[i][j] == 1)
				draw_square(god, i, j, god->pixels_per_x, god->pixels_per_y);
		}
	}
}

//draws one vertical slice
void draw_vertical(t_god *god, t_dda* dda, float wall_len, int x)
{
	int draw_start;
	int draw_end;
	int middle;

	middle = WINDOW_SIZE_Y / 2;
	draw_start = middle - wall_len / 2;
	draw_end = middle + wall_len / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WINDOW_SIZE_Y)
		draw_end = WINDOW_SIZE_Y - 1;
	if (draw_start < 0 || draw_start > WINDOW_SIZE_Y)
		draw_start = 0;
	if (draw_end >= WINDOW_SIZE_Y || draw_end < 0)
		draw_end = WINDOW_SIZE_Y - 1;
	ft_draw_line(god, x, 0, x, draw_start - 1, COLOR_CEILING);
	if (dda->which_wall_hit)
		ft_draw_line(god, x, draw_start, x, draw_end, COLOR_WALL / 2);
	else
		ft_draw_line(god, x, draw_start, x, draw_end, COLOR_WALL);
	ft_draw_line(god, x, draw_end + 1, x, WINDOW_SIZE_Y, COLOR_FLOOR);
}
