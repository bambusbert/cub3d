/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:46:01 by slambert          #+#    #+#             */
/*   Updated: 2026/07/22 14:24:48 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define WALL_CHAR 1
# define PLAYER_CHAR 2 // TODO use that
# define MAX_DIST_TO_WALL 0.2

# define SPRITE_WALL_N "./sprites/wall_n.xpm"
# define SPRITE_WALL_S "./sprites/wall_s.xpm"
# define SPRITE_WALL_W "./sprites/wall_w.xpm"
# define SPRITE_WALL_E "./sprites/wall_e.xpm"

# define PI 3.14159265358979323846
# define LEFT -1
# define RIGHT 1
# define FORWARD 1
# define BACK -1
# define ANGLE_OFFSET 0.5 // defines FOV / 2
# define SENSITIVITY 4
# define MOVE_TICK 8

# define FPS_CAP 60 // TODO implement fps cap or remove

# define WSIZE_X 800
# define WSIZE_Y 600
# define XCOORD 1
# define YCOORD 2

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define COLOR_ORANGE 551515151
# define COLOR_BLUE 0x0000FF
# define COLOR_RED 0xFF0000
# define COLOR_YELLOW 0xFFFF00
# define COLOR_WHITE 0xFFFFFF
# define COLOR_PIGGYPINK 0xFF77BA
# define COLOR_GREY 0x555555
# define COLOR_ERROR 0xDC3545

# define COLOR_CEILING COLOR_GREY
# define COLOR_FLOOR COLOR_PIGGYPINK

# define KEYDOWN_EV 2
# define KEYUP_EV 3
# define MOUSE_EV 6
# define CLOSING_EV 17
# define NO_EV_MASK 0
# define KEY_PRESS_MASK 1L << 0
# define KEY_RELEASE_MASK 1L << 1
# define POINTER_MOTION_MASK 1L << 6

// BONUS
# define MINIMAP_FACTOR 5
# define MINIMAP_BEAM_L 150
enum				e_direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

typedef struct s_ipoint
{
	int				x;
	int				y;
}					t_ipoint;

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
	int				img_bpp;
	int				img_ll;
	int				img_endian;
}					t_texture;

typedef struct s_god
{
	void			*mlx;
	void			*mlx_win;
	long long		time_last_frame_usec;
	float			time_since_last_frame_sec;
	// img stuff
	//TODO change that to be a t_texture
	void			*img;
	char			*img_addr;
	int				img_bpp;
	int				img_ll;
	int				img_endian;

	char **map;        // frido
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
	float			wall_dist; // WINDOW_SIZE_Y / distance is line height
	float			beam_dist;
	float			hit_x;
	float			hit_y;
	int				wall_start;
	int				wall_end;
	int				wall_len;
}					t_dda;

// debug.c - das kommt alles weg oder in bonus
void				print_keys(t_god *god);
char				**create_sample_map(t_god *god);
void				debug_init_player(t_god *god);
int					return_wall_color(int which_wall_hit);
void				fps_counter(t_god *god);
// int					mouse_function(void *param);

// bonus.c
int	mouse_move_function(int x, int y, void *param); // TODO das in bonus
void				draw_minimap_beams(t_god *god);

// cub3d.c
void				render(t_god *god);

// check_input.c
void				check_input(int argc, char **argv);

// init.c
void				init_god(t_god *god);

// input_handling.c
int					key_press(int keycode, void *param);
int					key_up(int keycode, void *param);

// helper.c
void				dda_single_ray(t_god *god, t_dda *dda, float angle, int x);
void				normalize_angle(float *angle);

// draw_main.c
void				dda_wrapper(t_god *god);
void				draw_2d_map(t_god *god);
void				draw_vertical(t_god *god, t_dda *dda, int x);

// draw_helper.c
void				draw_square(t_god *god, int row, int col);
void				my_mlx_pixel_put(t_god *god, int x, int y, int color);
void				ft_draw_line(t_god *god, t_ipoint p1, t_ipoint p2,
						int color);

// movement.c
void				position_manager(t_god *god);
void				update_player_angle(t_god *god, int direction);

// libft
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
size_t				ft_putstr_fd(char *s, int fd);
size_t				ft_strlen(const char *str);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

// dda_init.c
void				init_dda_struct(t_dda *dda, t_god *god, float beam_angle);

// init_textures.c
void				init_textures(t_god *god);

// time.c
long long			return_usecs_since_1970(void);
void				update_time_since_last_frame(t_god *god);

// cleanup.c
void				close_window(t_god *god);
void				error_exit(char *msg, t_god *god);

// unsorted

#endif
