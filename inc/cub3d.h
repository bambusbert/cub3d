/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:46:01 by slambert          #+#    #+#             */
/*   Updated: 2026/07/16 19:08:49 by slambert         ###   ########.fr       */
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
# include <sys/time.h>
# include <unistd.h>

# define WALL_CHAR 1
// TODO #define PLAYER_CHAR 2 and check for that and not hardcoded 2
# define MAX_DIST_TO_WALL 0.2

# define SPRITE_WALL_N "./sprites/wall_n.xpm"
# define SPRITE_WALL_S "./sprites/wall_s.xpm"
# define SPRITE_WALL_W "./sprites/wall_w.xpm"
# define SPRITE_WALL_E "./sprites/wall_e.xpm"

// if that is set to 1 than the minimap gets drawn instead of 3d view
# define DEBUG_MODE 1

# define PI 3.14159265
# define LEFT -1
# define RIGHT 1
# define FORWARD 1
# define BACK -1
//# define ANGLE_FRACTION 0.0175 // equals 1 degree
# define ANGLE_OFFSET 0.5 // defines FOV / 2
# define SENSITIVITY 0.015
# define MOVE_TICK 0.025

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
# define KEY_T 116
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define COLOR_ORANGE 551515151
# define COLOR_BLUE 0x0000FF
# define COLOR_RED 0xFF0000
# define COLOR_YELLOW 0xFFFF00
# define COLOR_WHITE 0xFFFFFF
# define COLOR_ERROR 0xDC3545
# define COLOR_CEILING 0x555555
# define COLOR_FLOOR 0xFF77BA
# define COLOR_WALL COLOR_BLUE

# define KEYDOWN_EVENT 2
# define KEYUP_EVENT 3
# define MOUSE_EVENT 6
# define CLOSING_EVENT 17

enum				e_direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_fpoint
{
	float			x;
	float			y;
}					t_fpoint;

typedef struct s_texture
{
	void			*img;
	char			*img_addr;
	int				width;
	int				height;
	int				img_bits_per_pixel;
	int				img_line_length;
	int				img_endian;
}					t_texture;

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

	char			**map;
	unsigned int rows; // frido
	unsigned int cols; // frido
	unsigned int	pixels_per_x;
	unsigned int	pixels_per_y;

	t_texture		*sprite_wall_S;
	t_texture		*sprite_wall_E;
	t_texture		*sprite_wall_N;
	t_texture		*sprite_wall_W;
	float player_x;             // frido
	float player_y;             // frido
	int player_start_direction; // frido
	float			player_angle;
	float			player_angle_min;
	float			player_angle_max;
	bool			debug_mode;
	bool			key_w;
	bool			key_a;
	bool			key_s;
	bool			key_d;
	bool			key_left;
	bool			key_right;
}					t_god;

typedef struct s_dda
{
	int				player_x_int;
	int				player_y_int;
	float			delta_x;
	float			delta_y;
	int				step_x;
	int				step_y;
	float			next_x;
	float			next_y;
	float			ray_dir_x;
	float			ray_dir_y;
	int				map_x;
	int				map_y;
	bool			wall_hit;
	bool			horizontal_wall_hit;
	int				which_wall_hit;
	float wall_dist; // WINDOW_SIZE_Y / distance is line height
	float			beam_dist;
	float			hit_x;
	float			hit_y;
	int				wall_start;
	int				wall_end;
	int				wall_len;
}					t_dda;

// debug.c - das kommt alles weg
void				print_keys(t_god *god);
char				**create_sample_map(t_god *p_god);
void				debug_init_player(t_god *god);
int					return_wall_color(int which_wall_hit);
void				fps_counter(void);

// cub3d.c
void				render(t_god *god);

// init.c
void				init_god(t_god *god);
void				initialize_map(t_god *p_god);

// input_handling.c
int					key_press(int keycode, void *param);
int					key_up(int keycode, void *param);

// helper.c
void				dda_single_ray(t_god *god, t_dda *dda, float beam_angle,
						int x);
void				visualize_2d_beam(t_god *god, t_dda *dda);
void				normalize_angle(float *angle);

// draw_main.c
void				dda_wrapper(t_god *god);
void				draw_2d_map(t_god *god);
void				draw_vertical(t_god *god, t_dda *dda, float wall_len,
						int x);

// draw_helper.c
void				draw_square(t_god *god, int row, int col);
void				my_mlx_pixel_put(t_god *god, int x, int y, int color);
void				ft_draw_line(t_god *god, t_point p1, t_point p2, int color);

// movement.c
int					position_manager(t_god *god);
void				update_player_angle(t_god *god, int direction);

// libft
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
size_t				ft_putstr_fd(char *s, int fd);

// dda_init.c
void				init_dda_struct(t_dda *dda, t_god *god, float beam_angle);

// init_textures.c
void				init_textures(t_god *p_god);

// cleanup.c
void				close_window(t_god *god);
void				error_exit(char *msg, t_god *p_god);

// unsorted

#endif
