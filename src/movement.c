/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:55:48 by slambert          #+#    #+#             */
/*   Updated: 2026/07/16 16:28:59 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// 360 degrees equals 2 pi (6.283)
void	update_player_angle(t_god *god, int direction)
{
	if (direction == LEFT)
		god->player_angle -= SENSITIVITY;
	else if (direction == RIGHT)
		god->player_angle += SENSITIVITY;
	normalize_angle(&god->player_angle);
	god->player_angle_min = god->player_angle - ANGLE_OFFSET;
	normalize_angle(&god->player_angle_min);
	god->player_angle_max = god->player_angle + ANGLE_OFFSET;
	normalize_angle(&god->player_angle_max);
}

static int	move_possible(t_god *god, float dx, float dy)
{
	float	new_x;
	float	new_y;
	int		x_change_dir;
	int		y_change_dir;

	x_change_dir = 1;
	y_change_dir = 1;
	new_x = god->player_x + dx;
	new_y = god->player_y + dy;
	if (new_x < god->player_x)
		x_change_dir = -1;
	if (new_y < god->player_y)
		y_change_dir = -1;
	new_x += x_change_dir * MAX_DIST_TO_WALL;
	new_y += y_change_dir * MAX_DIST_TO_WALL;
	if (god->map[(int)new_y][(int)new_x] == WALL_CHAR)
		return (0);
	return (1);
}

static int	move_vertical(t_god *god, int dir)
{
	float	dx;
	float	dy;

	dx = MOVE_TICK * cos(god->player_angle) * dir;
	dy = MOVE_TICK * sin(god->player_angle) * dir;
	if (!move_possible(god, dx, dy))
		return (0);
	god->player_x += dx;
	god->player_y += dy;
	return (1);
}

static int	move_horizontal(t_god *god, int dir)
{
	float	dx;
	float	dy;

	dx = MOVE_TICK * cos(god->player_angle + (PI / 2)) * dir;
	dy = MOVE_TICK * sin(god->player_angle + (PI / 2)) * dir;
	if (!move_possible(god, dx, dy))
		return (0);
	god->player_x += dx;
	god->player_y += dy;
	return (1);
}

// we can't change the players position each time bc the game would be way
// too fast like that. should we implement some kind of tick? static var?
// or is there some mlx magic we can use
int	position_manager(t_god *god)
{
	int	moved;

	moved = 0;
	if (god->key_w && !god->key_s)
		moved |= move_vertical(god, FORWARD);
	if (god->key_s && !god->key_w)
		moved |= move_vertical(god, BACK);
	if (god->key_d && !god->key_a)
		moved |= move_horizontal(god, RIGHT);
	if (god->key_a && !god->key_d)
		moved |= move_horizontal(god, LEFT);
	return (moved);
}
