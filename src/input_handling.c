/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 14:19:13 by slambert          #+#    #+#             */
/*   Updated: 2026/07/01 13:55:52 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	key_press(int keycode, void *param)
{
	t_god	*god;

	god = (t_god *)param;
	//printf("%d\n", keycode);
	if (keycode == KEY_W)
		god->key_w = true;
	else if (keycode == KEY_A)
		god->key_a = true;
	else if (keycode == KEY_S)
		god->key_s = true;
	else if (keycode == KEY_D)
		god->key_d = true;
	else if (keycode == KEY_LEFT)
		god->key_left = true;
	else if (keycode == KEY_RIGHT)
		god->key_right = true;
	else if (keycode == KEY_ESC)
		close_window(god);
	else if (keycode == KEY_T)
		god->debug_mode = !god->debug_mode;
	return (1);
}

int	key_up(int keycode, void *param)
{
	t_god *god;

	god = (t_god *)param;
	if (keycode == KEY_W)
		god->key_w = false;
	else if (keycode == KEY_A)
		god->key_a = false;
	else if (keycode == KEY_S)
		god->key_s = false;
	else if (keycode == KEY_D)
		god->key_d = false;
	else if (keycode == KEY_LEFT)
		god->key_left = false;
	else if (keycode == KEY_RIGHT)
		god->key_right = false;
	return (1);
}
