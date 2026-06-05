/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:46:16 by slambert          #+#    #+#             */
/*   Updated: 2026/06/05 17:48:13 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	key_hook(int keycode, t_god *god)
{
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
	if (keycode == KEY_ESC)
		close_window(god);
	return (0);
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
	mlx_key_hook(god->mlx_win, key_hook, god);
	mlx_loop(god->mlx);
}

int **create_sample_map(t_god *p_god)
{
    int rows = 7;
    int cols = 6;
	
	p_god->rows = rows;
	p_god->cols = cols;
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