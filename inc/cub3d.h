/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:46:01 by slambert          #+#    #+#             */
/*   Updated: 2026/07/01 14:50:53 by slambert         ###   ########.fr       */
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

# define WALL_CHAR 1
//TODO #define PLAYER_CHAR 2 and check for that and not hardcoded 2
# define MAX_DIST_TO_WALL 0.08 

# define SPRITE_PLAYER "./sprites/player.xpm"
# define SPRITE_WALL_N "./sprites/wall_e.xpm"
# define SPRITE_WALL_S "./sprites/wall_s.xpm"
# define SPRITE_WALL_W "./sprites/wall_w.xpm"
# define SPRITE_WALL_E "./sprites/wall_e.xpm"

//if that is set to 1 than the minimap gets drawn instead of 3d view
# define DEBUG_MODE 1

# define PI 3.14159265
# define LEFT 1
# define RIGHT 2
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
# define COLOR_CEILING 0x555555
# define COLOR_FLOOR 0xFF77BA
# define COLOR_WALL COLOR_BLUE

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
	bool			debug_mode;
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
	void			*sprite_player;
	void			*sprite_wall_S;
	void			*sprite_wall_E;
	void			*sprite_wall_N;
	void			*sprite_wall_W;
	float			player_x;
	float			player_y;
	float			player_angle;
	float			player_angle_min;
	float			player_angle_max;
	float			angle_offset;
	// float			angle_tick;
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
	bool which_wall_hit; // true if horizontal and false for vertical
	//for the 4 wall sprites we would need not only this info but also
	//the info north and south was hit
	float wall_dist;          // WINDOW_SIZE_Y / distance is line height
	float beam_dist;
	float			hit_x;
	float			hit_y;
}					t_dda;

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
void				dda_single_ray(t_god *god, float beam_angle, int x);
void				ft_draw_line(t_god *god, int x1, int y1, int x2, int y2,
						int color);
void	visualize_2d_beam(t_god *god, t_dda *dda);
						
// draw.c
void				dda_wrapper(t_god *god);
void				draw_2d_map(t_god *god);
void draw_vertical(t_god *god, t_dda* dda, float wall_len, int x);
void				my_mlx_pixel_put(t_god *god, int x, int y, int color);

// movement.c
int					position_handler(t_god *god);

// libft
void				ft_bzero(void *s, size_t n);

//dda_init.c
void init_dda_struct(t_dda *dda, t_god *god, float beam_angle);

// unsorted
void				*ft_calloc(size_t nmemb, size_t size);
void				error_exit(char *msg, t_god *p_god);
size_t				ft_putstr_fd(char *s, int fd);
int					close_window(t_god *god);
void				destroy_sprites(t_god *p_god);
void				normalize_angle(float *angle);
void render(t_god *god);
#endif