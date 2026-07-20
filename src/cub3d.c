/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:46:16 by slambert          #+#    #+#             */
/*   Updated: 2026/07/20 17:41:50 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	rotation_manager(t_god *god)
{
	if (god->key_left && god->key_right)
		return ;
	if (god->key_left)
		return (update_player_angle(god, LEFT));
	if (god->key_right)
		return (update_player_angle(god, RIGHT));
}

// TODO frame cap? e.g. 60Hz
void	render(t_god *god)
{
	ft_bzero(god->img_addr, WSIZE_Y * god->img_ll);
	dda_wrapper(god);
	draw_2d_map(god);
	draw_minimap_beams(god);
	mlx_put_image_to_window(god->mlx, god->mlx_win, god->img, 0, 0);
}

int	game_loop(t_god *god)
{
	update_time_since_last_frame(god);
	fps_counter(god);
	rotation_manager(god);
	position_manager(god);
	render(god);
	return (1);
}

void	game_function(t_god *god)
{
	god->mlx = mlx_init();
	if (!god->mlx)
		error_exit("Error\nMLX init failed\n", god);
	init_textures(god);
	god->mlx_win = mlx_new_window(god->mlx, WSIZE_X, WSIZE_Y, "cub3d");
	if (!god->mlx_win)
		error_exit("Error\nmlx_new_window failed\n", god);
	mlx_hook(god->mlx_win, CLOSING_EV, NO_EV_MASK, (int (*)(void))close_window, god);
	mlx_hook(god->mlx_win, KEYDOWN_EV, KEY_PRESS_MASK, (int (*)(void))key_press, god);
	mlx_hook(god->mlx_win, KEYUP_EV, KEY_RELEASE_MASK, (int (*)(void))key_up, god);
	// this works on mouse click
	// mlx_mouse_hook(god->mlx_win, (int (*)(void))mouse_function, god);
	// this on mouse move
	mlx_hook(god->mlx_win, MOUSE_EV, POINTER_MOTION_MASK,
		(int (*)(void))mouse_move_function, god);
	init_god(god);
	//mlx_do_key_autorepeatoff(god->mlx);
	render(god);
	god->time_last_frame_usec = return_usecs_since_1970();
	mlx_loop_hook(god->mlx, (int (*)(void))game_loop, god);
	mlx_loop(god->mlx);
}

// TODO argument check (one arg? correct file ending?)
int	main(int argc, char **argv)
{
	t_god	*god;

	(void)argc;
	(void)argv;
	// check_input (argc, argv);
	god = ft_calloc(1, sizeof(t_god));
	if (!god)
		return (printf("Error\ngod struct malloc fail\n"), 1);
	// FRIDO ENTRY POINT - parsing
	god->map = create_sample_map(god);
	game_function(god);
}
