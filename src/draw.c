/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 15:46:53 by slambert          #+#    #+#             */
/*   Updated: 2026/07/15 19:29:59 by slambert         ###   ########.fr       */
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
	// int hheight = tex->height - 1;
	// int wwidth = tex->width - 1;
	
	//int xp;
	//int yp;
	//color = tex->img_addr + (int) tex->width * tex_x;
	
	//x-Anteil - wie weit nach rechts in der texture:
	//xp = (int)(tex->width * tex_x);

	//y-Anteil - wie weit nach unten in der texture::
	//yp = (int)(tex->height * tex_y);
	
	//my_mlx_pixel_put(god, x, y, COLOR_ERROR);
	
	color = tex->img_addr + ((int)(tex->height * tex_y) * tex->img_line_length + (int)(tex->width * tex_x) * (tex->img_bits_per_pixel / 8));
	
	my_mlx_pixel_put(god, x, y, *(unsigned int *)color);
}

void draw_wall_texture_slice(t_god *god, int x, int y1, int y2, t_dda *dda)
{
	float wall_x; //aka tex_x
	float wall_y; //aka tex_y
	float step;
	t_texture *tex;
	
	if (!dda->horizontal_wall_hit)
		wall_x = fmod(dda->hit_x, 1);
	else
		wall_x = fmod(dda->hit_y, 1);
	//wall_x holds the information on where the wall was hit. i have to draw the
	//wall_x % column of the corresponding wall texture. if wall_x is 0.5 we
	//want to display the column in the middle of the texture.
	//printf("wall_x is %f\n", wall_x);
	if (dda->which_wall_hit == NORTH)
		tex = god->sprite_wall_N;
	else if (dda->which_wall_hit == EAST)
		tex = god->sprite_wall_E;
	else if (dda->which_wall_hit == SOUTH)
		tex = god->sprite_wall_S;
	else if (dda->which_wall_hit == WEST)
		tex = god->sprite_wall_W;
	//we have to loop through each pixel to be drawn
	//i think we have to calculate the step here ()
	step = 1.0 / (y2 - y1);
	wall_y = 0;
	while (y1 <= y2)
	{
		print_single_texel(god, x, y1, wall_x, wall_y, tex);
		wall_y += step;
		y1++;
		//printf("step is %f\n", step);
	}
}

//draws one vertical slice. a slice contains of the ceiling, the wall
//and the floor (up ---> down)
//atm we just print a color for the walls. TODO change that so that
//1 of 4 different sprites are printed
void draw_vertical(t_god *god, t_dda* dda, float wall_len, int x)
{
	int wall_start;
	int wall_end;
	int middle;

	middle = WINDOW_SIZE_Y / 2;
	wall_start = middle - wall_len / 2;
	wall_end = middle + wall_len / 2;
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end >= WINDOW_SIZE_Y)
		wall_end = WINDOW_SIZE_Y - 1;
	if (wall_start < 0 || wall_start > WINDOW_SIZE_Y)
		wall_start = 0;
	if (wall_end >= WINDOW_SIZE_Y || wall_end < 0)
		wall_end = WINDOW_SIZE_Y - 1;
	ft_draw_line(god, x, 0, x, wall_start - 1, COLOR_CEILING);
	// if (dda->horizontal_wall_hit)
	// 	ft_draw_line(god, x, wall_start, x, wall_end, (COLOR_WALL / 2));
	// else
	// 	ft_draw_line(god, x, wall_start, x, wall_end, COLOR_WALL);

	
	//ft_draw_line(god, x, wall_start, x, wall_end, return_wall_color(dda->which_wall_hit));
	draw_wall_texture_slice(god, x, wall_start, wall_end, dda);
	ft_draw_line(god, x, wall_end + 1, x, WINDOW_SIZE_Y, COLOR_FLOOR);
	//rand *= 1.00001;
}
