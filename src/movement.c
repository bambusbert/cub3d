/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:55:48 by slambert          #+#    #+#             */
/*   Updated: 2026/07/01 12:32:12 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// static int move_possible(t_god *god, float dx, float dy)
// {
//     float new_x;
//     float new_y;
    
//     new_x = god->player_x + dx;
//     new_y = god->player_y + dy;
//     if (god->map[(int)new_y][(int)new_x] == WALL_CHAR)
//         return 0;
//     return 1;
// }

static int move_possible(t_god *god, float dx, float dy)
{
    float new_x;
    float new_y;
    int x_change_dir;
    int y_change_dir;
    
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
        return 0;
    return 1;
}

static void move_back(t_god *god)
{
    float dx;
    float dy;

    dx = MOVE_TICK * cos(god->player_angle);
    dy = MOVE_TICK * sin(god->player_angle);
    if (!move_possible(god, -dx, -dy))
        return;
    god->player_x -= dx;
    god->player_y -= dy;
}

static void move_forward(t_god *god)
{
    float dx;
    float dy;

    dx = MOVE_TICK * cos(god->player_angle);
    dy = MOVE_TICK * sin(god->player_angle);
    if (!move_possible(god, dx, dy))
        return;
    god->player_x += dx;
    god->player_y += dy;
}

static void move_left(t_god *god)
{
    float dx;
    float dy;

    dx = MOVE_TICK * cos(god->player_angle - (PI / 2));
    dy = MOVE_TICK * sin(god->player_angle - (PI / 2));
    if (!move_possible(god, dx, dy))
        return;    
    god->player_x += dx;
    god->player_y += dy;
}

static void move_right(t_god *god)
{
    float dx;
    float dy;

    dx = MOVE_TICK * cos(god->player_angle - (PI / 2));
    dy = MOVE_TICK * sin(god->player_angle - (PI / 2));
    if (!move_possible(god, -dx, -dy))
        return;    
    god->player_x -= dx;
    god->player_y -= dy;
}

//we can't change the players position each time bc the game would be way
//too fast like that. should we implement some kind of tick? static var?
//or is there some mlx magic we can use
//possible TODO: add 45 degree movement (e.g. W + A)
//possible TODO: implement wall sliding. for that i would have to implement
//separate horizontal and vertical checks
int	position_handler (t_god *god)
{
	if (god->key_w && god->key_s)
		return 0;
	if (god->key_a && god->key_d)
		return 0;
    //that could be the llogic for 45 degree movement
    //if (god->key_w && god->key_a)
	//	return (move_left_up(god), 1);
	if (god->key_w)
		return (move_forward(god), 1);
	if (god->key_s)
		return (move_back(god), 1);
	if (god->key_a)
		return (move_left(god), 1);
	if (god->key_d)
		return (move_right(god), 1);
	return 0;
}
