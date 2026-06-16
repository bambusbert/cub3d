/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 14:58:18 by slambert          #+#    #+#             */
/*   Updated: 2026/06/16 12:12:16 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*	1.	calculate dx and dy. these distances are the x any y values the line to
 *		be drawn travels (line = hypothenuse, dx and dy kathete).
 *	2.	calculate the step. this is the max of the absolute values of dx and dy.
 *	3.	calculate dx and dy PER STEP - divide by step.
 *		(start from point 1 - x1 & y1)
 *	4.	loop from i to step and increment by the values from 3.
 *		round to nearest pixel.
 */
//TODO:	this is very slow. change to image buffer (calculate memory adresses &
//		change color value directly in memory)
void    ft_draw_line(t_god *god, int x1, int y1, int x2, int y2, int color)
{
    float   step;
    float   x;
    float   y;
    float   delta_x;
    float   delta_y;
    int     i;

    delta_x = x2 - x1;
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
        mlx_pixel_put(god->mlx, god->mlx_win, (int)round(x), (int)round(y), color);
        x += delta_x;
        y += delta_y;
    }
}

int	normalize_coordinate(int coord, int type)
{
	if (type == XCOORD)
		return (coord + WINDOW_SIZE_X / 2);
	else if (type == YCOORD)
		return (coord + WINDOW_SIZE_Y / 2);
	else
		return (-666);
}

// atm this function draws a beam from the middle to another 2d point.
// this should be enough but we have to keep in mind to update the
// relative position from the player (he is always in the middle bc FPV)
// but his position is different on the map

void	draw_beam_from_center(t_god *god, float beam_angle)
{
	int	count;
	int	pixel_x;
	int	pixel_y;
	int	len;
	int	color;
	float shifted_angle;

	count = 0;
	len = 50;
	shifted_angle = beam_angle - (PI / 2);
	pixel_x = len * cos(shifted_angle);
	pixel_y = len * sin(shifted_angle);
	color = 551515151;
	ft_draw_line(god, normalize_coordinate(0, XCOORD), normalize_coordinate(0,YCOORD), normalize_coordinate(pixel_x, XCOORD),	normalize_coordinate(pixel_y, YCOORD), color);
	// while (count++ < 100)
	// {
	// 	mlx_pixel_put(god->mlx, god->mlx_win, pixel_x + WINDOW_SIZE_X / 2,
	// 		pixel_y + WINDOW_SIZE_Y / 2, color);
	// 	// update pixel_x and pixel_y
	// }
}
