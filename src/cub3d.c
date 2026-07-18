/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:46:16 by slambert          #+#    #+#             */
/*   Updated: 2026/07/18 14:00:38 by slambert         ###   ########.fr       */
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

// if i want to implement an FPS counter, i need to be aware that with the
// current implementation i have 0 FPS if the player does not move or rotate
// OR is FPS considered how many times per second game_loop runs?
// possible FPS counter here, gettimeofday is allowed
// TODO remove the frame count var & printf
void	render(t_god *god)
{
	fps_counter();
	ft_bzero(god->img_addr, WSIZE_Y * god->img_ll);
	dda_wrapper(god);
	draw_2d_map(god);
	mlx_put_image_to_window(god->mlx, god->mlx_win, god->img, 0, 0);
}

// this is the entry for the raycasting logic. will get executed once per frame
//(do we have fixed fps? or is it just a while(1) loop?)
// theoretically i don't have to render on a fixed time interval but
// only on any key press?
int	game_loop(t_god *god)
{
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
	mlx_hook(god->mlx_win, CLOSING_EV, 0, (int (*)(void))close_window, god);
	mlx_hook(god->mlx_win, KEYDOWN_EV, 1L << 0, (int (*)(void))key_press, god);
	mlx_hook(god->mlx_win, KEYUP_EV, 1L << 1, (int (*)(void))key_up, god);
	// this works on mouse click
	// mlx_mouse_hook(god->mlx_win, (int (*)(void))mouse_function, god);
	// this on mouse move
	mlx_hook(god->mlx_win, MOUSE_EV, 1L << 6,
		(int (*)(void))mouse_move_function, god);
	init_god(god);
	mlx_do_key_autorepeatoff(god->mlx);
	render(god);
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
