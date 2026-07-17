/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 14:47:55 by slambert          #+#    #+#             */
/*   Updated: 2026/07/17 17:33:36 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	my_mlx_pixel_put(t_god *god, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WSIZE_X || y < 0 || y >= WSIZE_Y)
		return ;
	dst = god->img_addr + (y * god->img_ll + x
			* (god->img_bpp / 8));
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
void	ft_draw_line(t_god *god, t_ipoint p1, t_ipoint p2, int color)
{
	float		step;
	t_fpoint	p;
	t_fpoint	delta;
	int			i;

	delta.x = (p2.x - p1.x);
	delta.y = p2.y - p1.y;
	if (abs((int)delta.x) >= abs((int)delta.y))
		step = abs((int)delta.x);
	else
		step = abs((int)delta.y);
	delta.x = delta.x / step;
	delta.y = delta.y / step;
	p.x = p1.x;
	p.y = p1.y;
	i = -1;
	while (++i <= step)
	{
		my_mlx_pixel_put(god, (int)round(p.x), (int)round(p.y), color);
		p.x += delta.x;
		p.y += delta.y;
	}
}

void	draw_square(t_god *god, int row, int col)
{
	int	cur_x;
	int	cur_y;
	int	start_x;
	int	start_y;

	start_x = col * god->pixels_per_x;
	start_y = row * god->pixels_per_y;
	cur_x = -1;
	while (++cur_x < (int)god->pixels_per_x)
	{
		cur_y = -1;
		while (++cur_y < (int)god->pixels_per_y)
		{
			my_mlx_pixel_put(god, cur_x / MINIMAP_FACTOR + start_x / MINIMAP_FACTOR, cur_y / MINIMAP_FACTOR + start_y / MINIMAP_FACTOR, COLOR_BLUE);
		}
	}
}
