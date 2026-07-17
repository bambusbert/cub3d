/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 15:46:53 by slambert          #+#    #+#             */
/*   Updated: 2026/07/17 16:37:38 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// atm only possible to draw recangular maps.
void	draw_2d_map(t_god *god)
{
	int	i;
	int	j;

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

void	print_single_texel(t_god *god, t_ipoint p, t_fpoint texp, t_texture *tex)
{
	char	*color;
	int		tex_x_int;
	int		tex_y_int;

	tex_x_int = (int)(tex->width * texp.x);
	tex_y_int = (int)(tex->height * texp.y);
	if (tex_x_int >= tex->width)
		tex_x_int = tex->width - 1;
	if (tex_y_int >= tex->height)
		tex_y_int = tex->height - 1;
	if (tex_x_int < 0)
		tex_x_int = 0;
	if (tex_y_int < 0)
		tex_y_int = 0;
	color = tex->img_addr + (tex_y_int * tex->img_line_length + tex_x_int
			* (tex->img_bits_per_pixel / 8));
	my_mlx_pixel_put(god, p.x, p.y, *(unsigned int *)color);
}

static t_texture	*set_tex(t_god *god, t_dda *dda)
{
	if (dda->which_wall_hit == NORTH)
		return (god->sprite_wall_N);
	else if (dda->which_wall_hit == EAST)
		return (god->sprite_wall_E);
	else if (dda->which_wall_hit == SOUTH)
		return (god->sprite_wall_S);
	else if (dda->which_wall_hit == WEST)
		return (god->sprite_wall_W);
	return (god->sprite_wall_N);
}

// If the wall goes off the top of the screen,
//	we must start reading the texture further down.
void	draw_wall_texture_slice(t_god *god, int x, t_dda *dda)
{
	float		step;
	int			unclamped_wall_start;
	t_texture	*tex;
	float		tex_x;
	float		tex_y;

	if (!dda->horizontal_wall_hit)
		tex_x = fmod(dda->hit_x, 1);
	else
		tex_x = fmod(dda->hit_y, 1);
	if (dda->which_wall_hit == WEST || dda->which_wall_hit == SOUTH)
		tex_x = 1 - tex_x;
	tex = set_tex(god, dda);
	step = 1.0 / dda->wall_len;
	unclamped_wall_start = (WSIZE_Y / 2) - (dda->wall_len / 2);
	tex_y = (dda->wall_start - unclamped_wall_start) * step;
	while (dda->wall_start <= dda->wall_end)
	{
		print_single_texel(god, (t_ipoint){x, dda->wall_start}, (t_fpoint){tex_x,
			tex_y}, tex);
		tex_y += step;
		dda->wall_start++;
	}
}

// draws one vertical slice. a slice contains of the ceiling, the wall
// and the floor (up ---> down)
// atm we just print a color for the walls. TODO change that so that
// 1 of 4 different sprites are printed
void	draw_vertical(t_god *god, t_dda *dda, float wall_len, int x)
{
	int	middle;

	middle = WSIZE_Y / 2;
	dda->wall_start = middle - wall_len / 2;
	dda->wall_end = middle + wall_len / 2;
	if (dda->wall_start < 0)
		dda->wall_start = 0;
	if (dda->wall_end >= WSIZE_Y)
		dda->wall_end = WSIZE_Y - 1;
	if (dda->wall_start < 0 || dda->wall_start > WSIZE_Y)
		dda->wall_start = 0;
	if (dda->wall_end >= WSIZE_Y || dda->wall_end < 0)
		dda->wall_end = WSIZE_Y - 1;
	ft_draw_line(god, (t_ipoint){x, 0}, (t_ipoint){x, dda->wall_start - 1},
		COLOR_CEILING);
	dda->wall_len = wall_len;
	draw_wall_texture_slice(god, x, dda);
	ft_draw_line(god, (t_ipoint){x, dda->wall_end + 1}, (t_ipoint){x,
		WSIZE_Y}, COLOR_FLOOR);
}
