/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 15:46:53 by slambert          #+#    #+#             */
/*   Updated: 2026/07/16 14:41:38 by slambert         ###   ########.fr       */
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
void	ft_draw_line(t_god *god, t_point p1, t_point p2, int color)
{
	float	step;
	float	x;
	float	y;
	float	delta_x;
	float	delta_y;
	int		i;

	delta_x = (p2.x - p1.x);
	delta_y = p2.y - p1.y;
	if (abs((int)delta_x) >= abs((int)delta_y))
		step = abs((int)delta_x);
	else
		step = abs((int)delta_y);
	delta_x = delta_x / step;
	delta_y = delta_y / step;
	x = p1.x;
	y = p1.y;
	i = -1;
	while (++i <= step)
	{
		my_mlx_pixel_put(god, (int)round(x), (int)round(y), color);
		x += delta_x;
		y += delta_y;
	}
}

void draw_square (t_god* god, int row, int col)
{
	int cur_x;
	int cur_y;
	int start_x;
	int start_y;
	
	start_x = col * god->pixels_per_x;
	start_y = row * god->pixels_per_y;
	cur_x = -1;
	while (++cur_x < (int)god->pixels_per_x)
	{
		cur_y = -1;
		while (++cur_y < (int)god->pixels_per_y)
		{
			my_mlx_pixel_put(god, cur_x + start_x, cur_y + start_y, COLOR_BLUE);
		}
	}
}

//atm only possible to draw recangular maps.
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
				draw_square(god, i, j);
		}
	}
}

void print_single_texel(t_god *god, int x, int y, float tex_x, float tex_y, t_texture *tex)
{
    char* color;
    int tex_x_int;
    int tex_y_int;

    tex_x_int = (int)(tex->width * tex_x);
    tex_y_int = (int)(tex->height * tex_y);
    if (tex_x_int >= tex->width) tex_x_int = tex->width - 1;
    if (tex_y_int >= tex->height) tex_y_int = tex->height - 1;
    if (tex_x_int < 0) tex_x_int = 0;
    if (tex_y_int < 0) tex_y_int = 0;
    color = tex->img_addr + (tex_y_int * tex->img_line_length + tex_x_int * (tex->img_bits_per_pixel / 8));
    my_mlx_pixel_put(god, x, y, *(unsigned int *)color);
}

static t_texture *set_tex(t_god *god, t_dda *dda)
{
	if (dda->which_wall_hit == NORTH)
		return god->sprite_wall_N;
	else if (dda->which_wall_hit == EAST)
		return god->sprite_wall_E;
	else if (dda->which_wall_hit == SOUTH)
		return god->sprite_wall_S;
	else if (dda->which_wall_hit == WEST)
		return god->sprite_wall_W;
}

void draw_wall_texture_slice(t_god *god, int x, t_dda *dda)
{
	float tex_x; //aka wall_x
	float tex_y; //aka wall_y
	float step;
	int unclamped_wall_start;
	t_texture *tex;
	
	if (!dda->horizontal_wall_hit)
		tex_x = fmod(dda->hit_x, 1);
	else
		tex_x = fmod(dda->hit_y, 1);
	if (dda->which_wall_hit == WEST || dda->which_wall_hit == SOUTH)
		tex_x = 1 - tex_x;
	tex = set_tex (god, dda);
	step = 1.0 / dda->wall_len;
	// If the wall goes off the top of the screen, we must start reading the texture further down.
    unclamped_wall_start = (WINDOW_SIZE_Y / 2) - (dda->wall_len / 2);
    tex_y = (dda->wall_start - unclamped_wall_start) * step;
	while (dda->wall_start <= dda->wall_end)
	{
		print_single_texel(god, x, dda->wall_start, tex_x, tex_y, tex);
		tex_y += step;
		dda->wall_start++;
	}
}

//draws one vertical slice. a slice contains of the ceiling, the wall
//and the floor (up ---> down)
//atm we just print a color for the walls. TODO change that so that
//1 of 4 different sprites are printed
void draw_vertical(t_god *god, t_dda* dda, float wall_len, int x)
{
	int middle;

	middle = WINDOW_SIZE_Y / 2;
	dda->wall_start = middle - wall_len / 2;
	dda->wall_end = middle + wall_len / 2;
	if (dda->wall_start < 0)
		dda->wall_start = 0;
	if (dda->wall_end >= WINDOW_SIZE_Y)
		dda->wall_end = WINDOW_SIZE_Y - 1;
	if (dda->wall_start < 0 || dda->wall_start > WINDOW_SIZE_Y)
		dda->wall_start = 0;
	if (dda->wall_end >= WINDOW_SIZE_Y || dda->wall_end < 0)
		dda->wall_end = WINDOW_SIZE_Y - 1;
	//ft_draw_line(god, x, 0, x, dda->wall_start - 1, COLOR_CEILING);
	//p1: x / 0 | p2: x / dda->wall_start - 1
	//ft_draw_line(god, x, 0, x, dda->wall_start - 1, COLOR_CEILING);
	ft_draw_line(god, (t_point){x, 0}, (t_point){x, dda->wall_start - 1}, COLOR_CEILING);
	dda->wall_len = wall_len;
	draw_wall_texture_slice(god, x, dda);
	//ft_draw_line(god, x, dda->wall_end + 1, x, WINDOW_SIZE_Y, COLOR_FLOOR);
	ft_draw_line(god, (t_point){x, dda->wall_end + 1},(t_point){x, WINDOW_SIZE_Y}, COLOR_FLOOR);
}
