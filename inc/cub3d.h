/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:46:01 by slambert          #+#    #+#             */
/*   Updated: 2026/06/17 15:56:51 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define SPRITE_PLAYER "./sprites/player.xpm"
# define SPRITE_WALL_N "./sprites/wall_e.xpm"
# define SPRITE_WALL_S "./sprites/wall_s.xpm"
# define SPRITE_WALL_W "./sprites/wall_w.xpm"
# define SPRITE_WALL_E "./sprites/wall_e.xpm"

# define PI 3.14159265
# define LEFT 1
# define RIGHT 2
# define ANGLE_FRACTION 0.0175 // equals 1 degree
# define ANGLE_OFFSET 0.5      // defines FOV
# define SENSITIVITY 0.025
# define MOVE_TICK 0.015

# define WINDOW_SIZE_X 800
# define WINDOW_SIZE_Y 600
# define XCOORD 1
# define YCOORD 2
# define TILE_SIZE_X 32
# define TILE_SIZE_Y 32

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define COLOR_ORANGE 551515151
# define COLOR_BLUE 0x0000FF

# define KEYDOWN_EVENT 2
# define KEYUP_EVENT 3
# define CLOSING_EVENT 17

typedef struct s_god
{
	void			*mlx;
	void			*mlx_win;
	// img stuff
	void			*img;
	char			*img_addr;
	int				img_bits_per_pixel;
	int				img_line_length;
	int				img_endian;
	int				**map;
	unsigned int	rows;
	unsigned int	cols;
	unsigned int	pixels_per_x;
	unsigned int	pixels_per_y;
	bool			key_w;
	bool			key_a;
	bool			key_s;
	bool			key_d;
	bool			key_left;
	bool			key_right;
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
	float			player_x;
	float			player_y;
	float			player_angle;
	// defines the funnel where casts are sent out
	float			angle_offset;
	// float			angle_tick;
	float			player_angle_min;
	float			player_angle_max;
}					t_god;

// debug.c
void				print_keys(t_god *god);
int					**create_sample_map(t_god *p_god);

// init.c
void				init_stuff(t_god *god);
void				initialize_map(t_god *p_god);

// input_handling.c
int					key_press(int keycode, void *param);
int					key_up(int keycode, void *param);

// laser.c
void				draw_beam_from_player_inefficient(t_god *god, float beam_angle);

// draw.c
void				draw_funnel_beams(t_god *god);
void				draw_2d_map(t_god *god);

// movement.c
int					position_handler(t_god *god);

// libft
void				ft_bzero(void *s, size_t n);

// unsorted
void				*ft_calloc(size_t nmemb, size_t size);
void				error_exit(char *msg, t_god *p_god);
size_t				ft_putstr_fd(char *s, int fd);
int					close_window(t_god *god);
void				destroy_sprites(t_god *p_god);
void				normalize_angle(float *angle);
void				my_mlx_pixel_put(t_god *god, int x, int y, int color);

#endif