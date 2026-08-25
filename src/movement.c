/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:55:48 by slambert          #+#    #+#             */
/*   Updated: 2026/08/24 14:40:49 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// 360 degrees equals 2 pi (6.283)
void	update_player_angle(t_god *god, int direction)
{
	if (direction == LEFT)
		god->player_angle -= SENSITIVITY * god->time_since_last_frame_sec;
	else if (direction == RIGHT)
		god->player_angle += SENSITIVITY * god->time_since_last_frame_sec;
	normalize_angle(&god->player_angle);
	god->player_angle_min = god->player_angle - ANGLE_OFFSET;
	normalize_angle(&god->player_angle_min);
	god->player_angle_max = god->player_angle + ANGLE_OFFSET;
	normalize_angle(&god->player_angle_max);
}

static int	move_possible(t_god *god, float dx, float dy)
{
    float	x;
    float	y;
    float	radius;

    radius = MAX_DIST_TO_WALL;
    x = god->player_x + dx;
    y = god->player_y + dy;
    if (god->map[(int)(y - radius)][(int)(x - radius)] == WALL_CHAR
        || god->map[(int)(y - radius)][(int)(x + radius)] == WALL_CHAR
        || god->map[(int)(y + radius)][(int)(x - radius)] == WALL_CHAR
        || god->map[(int)(y + radius)][(int)(x + radius)] == WALL_CHAR)
        return (0);
    return (1);
}

static void	move_vertical(t_god *god, int dir)
{
	float	dx;
	float	dy;

	dx = MOVE_TICK * god->time_since_last_frame_sec * cos(god->player_angle)
		* dir;
	dy = MOVE_TICK * god->time_since_last_frame_sec * sin(god->player_angle)
		* dir;
	if (!move_possible(god, dx, dy))
		return ;
	god->player_x += dx;
	god->player_y += dy;
}

static void	move_horizontal(t_god *god, int dir)
{
	float	dx;
	float	dy;

	dx = MOVE_TICK * god->time_since_last_frame_sec * cos(god->player_angle
			+ (PI / 2)) * dir;
	dy = MOVE_TICK * god->time_since_last_frame_sec * sin(god->player_angle
			+ (PI / 2)) * dir;
	if (!move_possible(god, dx, dy))
		return ;
	god->player_x += dx;
	god->player_y += dy;
}

// we can't change the players position each time bc the game would be way
// too fast like that. should we implement some kind of tick? static var?
// or is there some mlx magic we can use
void	position_manager(t_god *god)
{
	if (god->key_w && !god->key_s)
		move_vertical(god, FORWARD);
	if (god->key_s && !god->key_w)
		move_vertical(god, BACK);
	if (god->key_d && !god->key_a)
		move_horizontal(god, RIGHT);
	if (god->key_a && !god->key_d)
		move_horizontal(god, LEFT);
}

// void	position_manager(t_god *god)
// {
// 	int	moved;

// 	moved = 0;
// 	if (god->key_w && !god->key_s)
// 		moved |= move_vertical(god, FORWARD);
// 	if (god->key_s && !god->key_w)
// 		moved |= move_vertical(god, BACK);
// 	if (god->key_d && !god->key_a)
// 		moved |= move_horizontal(god, RIGHT);
// 	if (god->key_a && !god->key_d)
// 		moved |= move_horizontal(god, LEFT);
// 	return (moved);
// }
