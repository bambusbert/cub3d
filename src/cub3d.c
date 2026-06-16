/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:46:16 by slambert          #+#    #+#             */
/*   Updated: 2026/06/16 12:45:36 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void update_player_position(t_god *god, int x, int y)
{
	god->player_x += x;
	god->player_y += y;
}

//possible TODO change into normalize_angles function that handles
//all 3 angle variables at once so we do not have 3 calls in update_player_angle
void normalize_angle (float *angle)
{
	if (*angle > 2 * PI)
		*angle -= 2 * PI;
	else if (*angle < 0)
		*angle += 2 * PI;
}

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

//we can't change the players position each time bc the game would be way
//too fast like that. should we implement some kind of tick? static var?
//or is there some mlx magic we can use
int	position_handler (t_god *god)
{
	//check for WASD keys
	//if smth is pressed, update the x and y position of the player
	//if (something pressed)
	// {
	// 	calculate movement
	// 	update position
	// 	return 1;
	// }
	return 0;
}

int get_no_beams(t_god *god)
{
	return (god->angle_offset * 2) * (1 / ANGLE_FRACTION);
}
void draw_funnel_beams(t_god *god)
{
	float angle_to_draw;
	int count;
	int no_beams;

	count = -1;
	no_beams = get_no_beams(god);
	angle_to_draw = god->player_angle_min;
	while (++count < no_beams)
	{
		normalize_angle(&angle_to_draw);
		draw_beam_from_center(god, angle_to_draw);
		angle_to_draw += god->angle_tick;
	}
}

//TODO performance (change from mlx_pixel_put to image)
void draw_square (t_god* god, int row, int col, int pixels_x, int pixels_y)
{
	int cur_x;
	int cur_y;
	int start_x;
	int start_y;
	int color;
	
	start_x = col * pixels_x;
	start_y = row * pixels_y;
	color = 551515151;
	cur_x = -1;
	while (++cur_x < pixels_x)
	{
		cur_y = -1;
		while (++cur_y < pixels_y)
		{
			mlx_pixel_put(god->mlx, god->mlx_win, cur_x + start_x, cur_y + start_y, color);
		}
	}
}

//atm only possible to draw recangular maps.
//TODO change that
void draw_2d_map(t_god* god)
{
	int i;
	int j;
	int pixels_x; //size of 1 square
	int pixels_y; //size of 1 square
	
	pixels_x = WINDOW_SIZE_X / god->cols;
	pixels_y = WINDOW_SIZE_Y / god->rows;
	i = -1;
	while (++i < god->rows)
	{
		j = -1;
		while (++j < god->cols)
		{
			if (god->map[i][j] == 1)
				draw_square(god, i, j, pixels_x, pixels_y);
		}
	}
}

void render(t_god *god)
{
	mlx_clear_window(god->mlx, god->mlx_win);
	//this is where the raycasting magic happens
	
	//DEBUG
	draw_2d_map(god);
	//DEBUG draw the beams in the funnel
	draw_funnel_beams(god);
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
