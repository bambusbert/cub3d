/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:46:16 by slambert          #+#    #+#             */
/*   Updated: 2026/06/15 14:11:56 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	initialize_map(t_god *p_god)
{
	int	w;
	int	h;

	p_god->sprite_player = mlx_xpm_file_to_image(p_god->mlx, SPRITE_PLAYER, &w, &h);
	if (!p_god->sprite_player)
		error_exit("Error\nerror in initialize_map: player sprite\n", p_god);
	p_god->sprite_wall_E = mlx_xpm_file_to_image(p_god->mlx,
			SPRITE_WALL_E, &w, &h);
	if (!p_god->sprite_wall_E)
		error_exit("Error\nerror in initialize_map: wall_E sprite\n", p_god);
	p_god->sprite_wall_N = mlx_xpm_file_to_image(p_god->mlx, SPRITE_WALL_N, &w, &h);
	if (!p_god->sprite_wall_N)
		error_exit("Error\nerror in initialize_map: wall_N sprite\n", p_god);
	p_god->sprite_wall_S = mlx_xpm_file_to_image(p_god->mlx, SPRITE_WALL_S, &w, &h);
	if (!p_god->sprite_wall_S)
		error_exit("Error\nerror in initialize_map: wall_S sprite\n", p_god);
	p_god->sprite_wall_W = mlx_xpm_file_to_image(p_god->mlx, SPRITE_WALL_W, &w, &h);
	if (!p_god->sprite_wall_W)
		error_exit("Error\nerror in initialize_map: wall_W sprite\n", p_god);
}

void update_player_position(t_god *god, int x, int y)
{
	god->player_x += x;
	god->player_y += y;
}

//360 degrees equals 2 pi
//TODO look into radian. if the angle gets bigger than 2pi, take that into account.
//modulo! also do this if the angle gets too small (negative)
//update god.playerangle
void update_player_angle (t_god *god, int direction)
{
	if (direction == LEFT)
		god->player_angle -= ANGLE_FRACTION;
	else if (direction == RIGHT)
		god->player_angle += ANGLE_FRACTION;
	//we can't use modulo operator for float numbers
	if (god->player_angle > 2 * PI)
		god->player_angle -= 2 * PI;
	else if (god->player_angle < 0)
		god->player_angle += 2 * PI;
	//printf("Player angle: %.3f\n", god->player_angle);

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

int	key_hook(int keycode, void *param)
{
	t_god	*god;

	god = (t_god *)param;
	if (keycode == KEY_W)
		ft_putstr_fd("W\n", 1);
		//move_player(god, -1, 0);
	if (keycode == KEY_A)
		ft_putstr_fd("A\n", 1);
		//move_player(god, 0, -1);
	if (keycode == KEY_D)
		ft_putstr_fd("D\n", 1);
		//move_player(god, 0, 1);
	if (keycode == KEY_S)
		ft_putstr_fd("S\n", 1);
		//move_player(god, 1, 0);
	//TODO change player angle when left/right is pressed
	if (keycode == KEY_LEFT)
	{
		ft_putstr_fd("Left\n", 1);
		update_player_angle(god, LEFT);
	}
	if (keycode == KEY_RIGHT)
	{
		ft_putstr_fd("Right\n", 1);		
		update_player_angle(god, RIGHT);
	}
	if (keycode == KEY_ESC)
		close_window(god);
	return (0);
}

void	print_keys(t_god *god)
{
	static int x = 0;
	if (x++ % 1000 != 0)
		return ;
	printf("Key: W | Status: %d\n", god->key_w);
	printf("Key: A | Status: %d\n", god->key_a);
	printf("Key: S | Status: %d\n", god->key_s);
	printf("Key: D | Status: %d\n", god->key_d);
	printf("Key: Left | Status: %d\n", god->key_left);
	printf("Key: Right | Status: %d\n", god->key_right);
	printf("Player x coordinate: %.2f\n", god->player_x);
	printf("Player y coordinate: %.2f\n", god->player_y);
	printf("Player Angle: %.3f\n", god->player_angle);
}

//this is the entry for the raycasting logic. will get executed once per frame
//(do we have fixed fps? or is it just a while(1) loop?)
//theoretically i don't have to render on a fixed time interval but only on any key press?
int	render_world(t_god *god)
{
	//debug print key status
	print_keys(god);
	//here we have to update everything. what exactly needs to be updated is regarding
	//which keys are currently pressed (info from the god struct)
	angle_handler(god);
	
	return 1;
}

void	init_stuff(t_god *god)
{
	// we should do something like:
	// int player_pos[2];

	// player_pos = get_player_position (god);
	// god->player_x = player_pos[0];
	// god->player_y = player_pos[1];

	//3/4 is a placeholder, that's the position of the player in the sample map
	god->player_x = 3;
	god->player_y = 4;

	//player_angle is initially 0 (NORTH)
	god->player_angle = 0;
	god->key_a = false;
	god->key_s = false;
	god->key_d = false;
	god->key_w = false;
	god->key_left = false;
	god->key_right = false;
}

//void	key_press (int keycode, t_god *god)
int	key_press (int keycode, void *param)
{
	t_god *god;

	god = (t_god*) param;
	//static int i = 0;
	//printf("key pressed\n");
	if (keycode == KEY_W)
	{
		//printf("W pressed %d\n", i++);
		god->key_w = true;
	}
	else if (keycode == KEY_A)
	{
		//printf("A pressed\n");
		god->key_a = true;
	}
	else if (keycode == KEY_S)
	{
		//printf("S pressed\n");
		god->key_s = true;
	}
	else if (keycode == KEY_D)
	{
		//printf("D pressed\n");
		god->key_d = true;
	}
	else if (keycode == KEY_LEFT)
	{
		//printf("left pressed\n");
		god->key_left = true;
	}
	else if (keycode == KEY_RIGHT)
	{
		//printf("right pressed\n");
		god->key_right = true;
	}
	else if (keycode == KEY_ESC)
	{
		//printf("ESC pressed\n");
		close_window(god);
	}
	
	
	return 1;
}

int	key_up (int keycode, void *param)
{
	t_god *god;

	god = (t_god*) param;
	//printf("key up\n");
	static int i = 0;
	if (keycode == KEY_W)
	{
		//printf("W up %d\n", i++);
		god->key_w = false;
	}
	else if (keycode == KEY_A)
	{
		//printf("A up\n");
		god->key_a = false;
	}
	else if (keycode == KEY_S)
	{
		//printf("S up\n");
		god->key_s = false;
	}
	else if (keycode == KEY_D)
	{
		//printf("D up\n");
		god->key_d = false;
	}
	else if (keycode == KEY_LEFT)
	{
		//printf("left up\n");
		god->key_left = false;
	}
	else if (keycode == KEY_RIGHT)
	{
		//printf("right up\n");
		god->key_right = false;
	}
	else if (keycode == KEY_ESC)
	{
		//brauch ma nima
		//printf("ESC up\n");
	}
	return 1;
}

void	game_function(t_god *god)
{
	god->mlx = mlx_init();
	if (!god->mlx)
		error_exit("Error\nMLX init failed\n", god);
	initialize_map(god);
	god->mlx_win = mlx_new_window(god->mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y, "so_long");
	if (!god->mlx_win)
		error_exit("Error\nmlx_new_window failed\n", god);
	mlx_hook(god->mlx_win, CLOSING_EVENT, 0, close_window, god);

	//mlx_hook(god->mlx_win, 3, 0, key_hook, god);
	//mlx_key_hook(god->mlx_win, key_hook, god);
	mlx_hook(god->mlx_win, KEYDOWN_EVENT, 1L<<0, key_press, god);
	mlx_hook(god->mlx_win, KEYUP_EVENT, 1L<<1, key_up, god);
	
	init_stuff(god);
	//render_world(god);
	mlx_do_key_autorepeatoff(god->mlx);
	mlx_loop_hook(god->mlx, render_world, god);
	mlx_loop(god->mlx);
	
}

int **create_sample_map(t_god *p_god)
{
    int rows = 7;
    int cols = 6;
	
	p_god->rows = rows;
	p_god->cols = cols;
	//Player currently is 2
    int static_map[7][6] = {
        {1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 1},
        {1, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 2, 1},
        {1, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 1}
    };
    int **map = (int**)ft_calloc(rows + 1, sizeof(int*));
    if (!map)
        return NULL;
    for (int i = 0; i < rows; i++)
    {
        map[i] = (int*)ft_calloc(cols, sizeof(int));
        if (!map[i])
            return NULL; 
        for (int j = 0; j < cols; j++)
            map[i][j] = static_map[i][j];
    }
    return map;
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
