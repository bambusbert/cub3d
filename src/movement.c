/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:55:48 by slambert          #+#    #+#             */
/*   Updated: 2026/06/16 16:57:27 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void move_forward(t_god *god)
{
    float dx;
    float dy;

    dx = MOVE_TICK * cos(god->player_angle - (PI / 2));
    dy = MOVE_TICK * sin(god->player_angle - (PI / 2));
    god->player_x += dx;
    god->player_y += dy;
}

static void move_back(t_god *god)
{
    float dx;
    float dy;

    dx = MOVE_TICK * cos(god->player_angle - (PI / 2));
    dy = MOVE_TICK * sin(god->player_angle - (PI / 2));
    god->player_x -= dx;
    god->player_y -= dy;
}

static void move_right(t_god *god)
{
    float dx;
    float dy;

    dx = MOVE_TICK * cos(god->player_angle);
    dy = MOVE_TICK * sin(god->player_angle);
    god->player_x += dx;
    god->player_y += dy;
}

static void move_left(t_god *god)
{
    float dx;
    float dy;

    dx = MOVE_TICK * cos(god->player_angle);
    dy = MOVE_TICK * sin(god->player_angle);
    god->player_x -= dx;
    god->player_y -= dy;
}

//we can't change the players position each time bc the game would be way
//too fast like that. should we implement some kind of tick? static var?
//or is there some mlx magic we can use
int	position_handler (t_god *god)
{
	if (god->key_w && god->key_s)
		return 0;
	if (god->key_a && god->key_d)
		return 0;
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
