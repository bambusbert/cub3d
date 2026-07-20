/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 14:20:57 by slambert          #+#    #+#             */
/*   Updated: 2026/07/20 15:08:14 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	print_keys(t_god *god)
{
	// static long x = 0;
	// if (x++ % 5 != 0)     //only print each 50th function call
	// 	return ;
	printf("Key: W | Status: %d\n", god->key_w);
	printf("Key: A | Status: %d\n", god->key_a);
	printf("Key: S | Status: %d\n", god->key_s);
	printf("Key: D | Status: %d\n", god->key_d);
	printf("Key: Left | Status: %d\n", god->key_left);
	printf("Key: Right | Status: %d\n", god->key_right);
	printf("Player x coordinate: %.2f\n", god->player_x);
	printf("Player y coordinate: %.2f\n", god->player_y);
	printf("Player Angle: %.3f\n", god->player_angle);
	printf("Player Angle min: %.3f\n", god->player_angle_min);
	printf("Player Angle max: %.3f\n", god->player_angle_max);
	printf("Pixels per x: %d\n", god->pixels_per_x);
	printf("Pixels per y: %d\n", god->pixels_per_y);
}

char	**create_sample_map(t_god *god)
{
	int		rows;
	int		cols;
	char	**map;

	rows = 30;
	cols = 20;
	god->rows = rows;
	god->cols = cols;
	// Player currently is 2
	char static_map[30][20] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
	map = (char **)ft_calloc(rows + 1, sizeof(char *));
	if (!map)
		return (NULL);
	for (int i = 0; i < rows; i++)
	{
		map[i] = (char *)ft_calloc(cols, sizeof(char));
		if (!map[i])
			return (NULL);
		for (int j = 0; j < cols; j++)
			map[i][j] = static_map[i][j];
	}
	return (map);
}

// TODO das kommt weg, die variablen werden von frido bwefüllt.
// finde PLAYER_CHARACTER in der map und setze player_x und player_y.
void	debug_init_player(t_god *god)
{
	god->player_x = 3;
	god->player_y = 4;
	god->player_start_direction = WEST;
}

// TODO das kommt weg, überbleibsel aus untextured raycaster
int	return_wall_color(int which_wall_hit)
{
	if (which_wall_hit == NORTH)
		return (COLOR_ORANGE);
	if (which_wall_hit == EAST)
		return (COLOR_RED);
	if (which_wall_hit == SOUTH)
		return (COLOR_YELLOW);
	if (which_wall_hit == WEST)
		return (COLOR_WHITE);
	return (COLOR_ERROR);
}

//TODO kommt weg
// atm bug at the very first frame
// void	fps_counter(t_god *god)
// {
// 	static int			frame_count = 0;
// 	static long	long time_last_frame = 0;
// 	long long			delta_time_usec;
// 	float				delta_time_sec;
// 	long long			current_time;
// 	float				fps;

// 	if (time_last_frame == 0)
// 		time_last_frame = return_usecs_since_1970();
// 	frame_count++;
// 	current_time = return_usecs_since_1970();
// 	delta_time_usec = current_time - time_last_frame;
// 	delta_time_sec = (float)delta_time_usec / 1000000;
// 	if (delta_time_usec / 1000 != 0)
// 		fps = (float)1 / (delta_time_sec);
// 	else
// 		delta_time_usec = 1;
// 	printf("%.1f FPS | Frame %d | t_s_l_f: %f\n", fps, frame_count, god->time_since_last_frame_sec);
// 	time_last_frame = return_usecs_since_1970();
// }

void	fps_counter(t_god *god)
{
	static int			frame_count = 0;
	float				fps;

	frame_count++;
	if (god->time_since_last_frame_sec != 0)
		fps = (float)1 / (god->time_since_last_frame_sec);
	else
		fps = 1;
	printf("%.1f FPS | Frame %d | t_s_l_f: %f\n", fps, frame_count, god->time_since_last_frame_sec);
}

// int	mouse_function(void *param)
// {
// 	t_god	*god;

// 	god = (t_god *)param;
// 	printf("Hello from mouse function\n");
// 	return (0);
// }

// int	mouse_move_function(int x, int y, void *param)
// {
// 	static int	delta_x = 0;
// 	int			min_offset;
// 	t_god		*god;

// 	min_offset = 10;
// 	god = (t_god *)param;
// 	mlx_mouse_hide(god->mlx, god->mlx_win);
// 	if (x > WSIZE_X / 2)
// 		delta_x++;
// 	else if (x < WSIZE_X / 2)
// 		delta_x--;
// 	if (delta_x >= min_offset)
// 	{
// 		update_player_angle(god, RIGHT);
// 		mlx_mouse_move(god->mlx, god->mlx_win, WSIZE_X / 2, WSIZE_Y / 2);
// 		render(god);
// 		delta_x = 0;
// 	}
// 	else if (delta_x <= min_offset * -1)
// 	{
// 		update_player_angle(god, LEFT);
// 		mlx_mouse_move(god->mlx, god->mlx_win, WSIZE_X / 2, WSIZE_Y / 2);
// 		render(god);
// 		delta_x = 0;
// 	}
// 	return (0);
// }

// TODO 3/4 is a placeholder,
//that's the position of the player in the sample map

// int **create_sample_map(t_god *god)
// {
//     int rows = 30;
//     int cols = 20;

// 	god->rows = rows;
// 	god->cols = cols;
// 	//Player currently is 2
//     int static_map[30][20] = {
//         {1, 1, 1, 1, 1, 1},
//         {1, 0, 0, 0, 0, 1},
//         {1, 1, 0, 0, 0, 1},
//         {1, 0, 1, 0, 2, 1},
//         {1, 1, 0, 0, 0, 1},
//         {1, 0, 0, 0, 0, 1},
//         {1, 1, 1, 1, 0, 1}
//     };
//     int **map = (int**)ft_calloc(rows + 1, sizeof(int*));
//     if (!map)
//         return (NULL);
//     for (int i = 0; i < rows; i++)
//     {
//         map[i] = (int*)ft_calloc(cols, sizeof(int));
//         if (!map[i])
//             return (NULL);
//         for (int j = 0; j < cols; j++)
//             map[i][j] = static_map[i][j];
//     }
//     return (map);
// }