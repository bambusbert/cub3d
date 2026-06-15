/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:46:01 by slambert          #+#    #+#             */
/*   Updated: 2026/06/15 14:10:31 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
#include <unistd.h>

# define SPRITE_PLAYER "./sprites/player.xpm"
# define SPRITE_WALL_N "./sprites/wall_e.xpm"
# define SPRITE_WALL_S "./sprites/wall_s.xpm"
# define SPRITE_WALL_W "./sprites/wall_w.xpm"
# define SPRITE_WALL_E "./sprites/wall_e.xpm"

# define PI 3.14159265
# define LEFT 1
# define RIGHT 2
# define ANGLE_FRACTION 0.0001

# define WINDOW_SIZE_X 800
# define WINDOW_SIZE_Y 600
# define TILE_SIZE_X 32
# define TILE_SIZE_Y 32

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define KEYDOWN_EVENT 2
# define KEYUP_EVENT 3
# define CLOSING_EVENT 17

typedef struct s_god
{
	void			*mlx;
	void			*mlx_win;
	int				**map;
	bool			key_w;
	bool			key_a;
	bool			key_s;
	bool			key_d;
	bool			key_left;
	bool			key_right;
	unsigned int	cols;
	unsigned int	rows;
	// unsigned int	count_collectible;
	// unsigned int	count_player;
	// unsigned int	count_exit;
	// unsigned int	count_wall;
	// unsigned int	count_empty;
	// unsigned int	player_col;
	// unsigned int	player_row;
	// unsigned int	exit_col;
	// unsigned int	exit_row;
	// unsigned int	moves;
	void			*sprite_player;
	void			*sprite_wall_S;
	void			*sprite_wall_E;
	void			*sprite_wall_N;
	void			*sprite_wall_W;
	// these also should be floats??
	float			player_x;
	float			player_y;
	float			player_angle;
}					t_god;

void				*ft_calloc(size_t nmemb, size_t size);
void				error_exit(char *msg, t_god *p_god);
size_t				ft_putstr_fd(char *s, int fd);
int					close_window(t_god *god) ;
void destroy_sprites(t_god *p_god);

#endif