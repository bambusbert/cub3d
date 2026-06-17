/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:46:16 by slambert          #+#    #+#             */
/*   Updated: 2026/06/16 17:14:32 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void update_player_position(t_god *god, int x, int y)
// {
// 	god->player_x += x;
// 	god->player_y += y;
// }

//360 degrees equals 2 pi (6.283)
void update_player_angle (t_god *god, int direction)
{
	if (direction == LEFT)
		god->player_angle -= SENSITIVITY;
	else if (direction == RIGHT)
		god->player_angle += SENSITIVITY;
	//we can't use modulo operator for float numbers
	normalize_angle(&god->player_angle);
	//printf("Player angle: %.3f\n", god->player_angle);
	//update player_angle_min and player_angle_max
	god->player_angle_min = god->player_angle - god->angle_offset;
	normalize_angle(&god->player_angle_min);
	god->player_angle_max = god->player_angle + god->angle_offset;
	normalize_angle(&god->player_angle_max);
}

void	angle_handler(t_god *god)
{
	if (god->key_left && god->key_right)
		return ;
	if (god->key_left)
		update_player_angle(god, LEFT);
	if (god->key_right)
		update_player_angle(god, RIGHT);
}

void render(t_god *god)
{
	//mlx_clear_window(god->mlx, god->mlx_win);
	//my_mlx_clear_window(god->mlx, god->mlx_win);
	//clear image
	ft_bzero(god->img_addr, WINDOW_SIZE_Y * god->img_line_length);
	//this is where the raycasting magic happens
	
	//DEBUG
	draw_2d_map(god);
	//DEBUG draw the beams in the funnel
	draw_funnel_beams(god);
	//mlx_destroy_image(god->mlx, god->img);
	mlx_put_image_to_window(god->mlx, god->mlx_win, god->img, 0, 0);
}

//this is the entry for the raycasting logic. will get executed once per frame
//(do we have fixed fps? or is it just a while(1) loop?)
//theoretically i don't have to render on a fixed time interval but only on any key press?
int	game_loop(t_god *god)
{
	//debug print key status
	print_keys(god);
	
	//here we have to update everything. what exactly needs to be updated is regarding
	//which keys are currently pressed (info from the god struct)
	angle_handler(god);
	
	//if wasd key(s) pressed, position handler returns 1
	//then we have to re-render
	if (position_handler(god))
		render(god);
	//for now we just render either way
	render(god);
	return 1;
}

void	game_function(t_god *god)
{
	god->mlx = mlx_init();
	if (!god->mlx)
		error_exit("Error\nMLX init failed\n", god);
	initialize_map(god);
	god->mlx_win = mlx_new_window(god->mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y, "cub3d");
	if (!god->mlx_win)
		error_exit("Error\nmlx_new_window failed\n", god);
	mlx_hook(god->mlx_win, CLOSING_EVENT, 0, close_window, god);

	//mlx_hook(god->mlx_win, 3, 0, key_hook, god);
	//mlx_key_hook(god->mlx_win, key_hook, god);
	mlx_hook(god->mlx_win, KEYDOWN_EVENT, 1L<<0, key_press, god);
	mlx_hook(god->mlx_win, KEYUP_EVENT, 1L<<1, key_up, god);
	
	init_stuff(god);
	mlx_do_key_autorepeatoff(god->mlx);
	//render(god);
	mlx_loop_hook(god->mlx, game_loop, god);
	mlx_loop(god->mlx);
}

int main (int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_god *p_god;
	p_god = ft_calloc(1, sizeof(t_god));

	p_god->map = create_sample_map(p_god);;
	game_function(p_god);
}
