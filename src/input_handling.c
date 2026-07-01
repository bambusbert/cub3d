/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 14:19:13 by slambert          #+#    #+#             */
/*   Updated: 2026/07/01 11:55:19 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void	key_press (int keycode, t_god *god)
int	key_press(int keycode, void *param)
{
	t_god	*god;

	god = (t_god *)param;
	// static int i = 0;
	// printf("key pressed\n");
	if (keycode == KEY_W)
	{
		// printf("W pressed %d\n", i++);
		god->key_w = true;
	}
	else if (keycode == KEY_A)
	{
		// printf("A pressed\n");
		god->key_a = true;
	}
	else if (keycode == KEY_S)
	{
		// printf("S pressed\n");
		god->key_s = true;
	}
	else if (keycode == KEY_D)
	{
		// printf("D pressed\n");
		god->key_d = true;
	}
	else if (keycode == KEY_LEFT)
	{
		// printf("left pressed\n");
		god->key_left = true;
	}
	else if (keycode == KEY_RIGHT)
	{
		// printf("right pressed\n");
		god->key_right = true;
	}
	else if (keycode == KEY_ESC)
	{
		// printf("ESC pressed\n");
		close_window(god);
	}
	return (1);
}

int	key_up(int keycode, void *param)
{
	t_god *god;

	god = (t_god *)param;
	// printf("key up\n");
	static int i = 0;
	if (keycode == KEY_W)
	{
		// printf("W up %d\n", i++);
		god->key_w = false;
	}
	else if (keycode == KEY_A)
	{
		// printf("A up\n");
		god->key_a = false;
	}
	else if (keycode == KEY_S)
	{
		// printf("S up\n");
		god->key_s = false;
	}
	else if (keycode == KEY_D)
	{
		// printf("D up\n");
		god->key_d = false;
	}
	else if (keycode == KEY_LEFT)
	{
		// printf("left up\n");
		god->key_left = false;
	}
	else if (keycode == KEY_RIGHT)
	{
		// printf("right up\n");
		god->key_right = false;
	}
	else if (keycode == KEY_ESC)
	{
		// brauch ma nima
		// printf("ESC up\n");
	}
	return (1);
}
