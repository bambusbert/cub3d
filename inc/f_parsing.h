#ifndef F_PARSING_H
# define F_PARSING_H

//# define LIMIT_DOWN -10
# define LIMIT_UP 255

#define _GNU_SOURCE
# include "../inc/cub3d.h"
# include "../f_db/f_db.h"
# include "../f_file_reader/f_read_file.h"
# include "../libft/libft.h"
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>

// struct prototypes

typedef struct s_color	t_color;
typedef struct s_read_map	t_read_map;

// f_commandline_input.c
bool					f_test_input(int ac, const char *s);

// f_parse_into_db.c
bool					f_parse_into_db(t_db *db, char *file);

// f_parse_colors.c
bool f_parse_colors(t_db *db, t_color *colors);
bool f_init_colors(t_color *colors);

// f_atol.c
uint32_t f_catch_num(char *s);
long long	f_atoll(char *arg);

// f_is_allowed.c
bool is_allowed(char c, t_read_map *m);

// f_parse_map.c
bool f_parse_map(t_db *db);

// f_parse_map2.c
bool f_test_map(t_db *db, t_read_map *m);

// f_for_stefan.c
bool for_fortnite_and_stefan(t_db *db, t_color *colors);

// f_from_stefan.c
bool f_from_stefan(t_db *db, char **map, t_color *colors);

//HAT STEFAN EINGEFÜGT
void	init_mlx_stuff(t_god *god);

// structs

typedef struct s_color
{
    char                key;
	uint32_t			r;
	uint32_t			g;
	uint32_t			b;
}						t_color;

typedef struct s_read_map
{
    int x;
    int y;
    int i;
    int j;
    int k;
    int mapsize;
    int fd;
    int xmax;
    char *buffer;
    const char* map;
    int n;
    int o;
    int s;
    int w;
    int pp;
}t_read_map;

#endif
