#include "../inc/f_parsing.h"

static enum e_direction f_define_player_direction(char c)
{
    if (c == 'N')
        return (NORTH);
    else if (c == 'E')
        return (EAST);
    else if (c == 'S')
        return (SOUTH);
    else if (c == 'W')
        return (WEST);
    return (enum e_direction) 600;
}

static void f_find_and_define_player(t_god *god, char **m, int i, int j)
{
    while (m[i])
    {
        j = 0;
        while (m[i][j])
        {
            if (m[i][j] == 'N' || m[i][j] == 'E' || m[i][j] == 'S' || m[i][j] == 'W')
            {
                god->player_start_direction = f_define_player_direction(m[i][j]);
                m[i][j] = PLAYER_CHAR;
                god->player_x = (float) j + 0.5;
                god->player_y = (float) i + 0.5;
                return ;
            }
            j++;
        }
        i++;
    }
}


static void set_colors(t_god *god, t_color *colors)
{
    int color_temp;

    color_temp = (((colors[0].r << 8) + colors[0].g ) << 8) + colors[0].b;
    god->color_floor = color_temp;
    color_temp = (((colors[1].r << 8) + colors[1].g ) << 8) + colors[1].b;
    god->color_ceiling = color_temp;
}

bool start_graphical_stuff(t_db *db, char **map, t_color *colors)
{
    t_god *god;

    god = ft_calloc(1, sizeof(t_god));
	if (!god)
		return (ft_putstr_fd("Error\ngod struct malloc fail\n", 2), false);
    god->db = db;
    god->map = map;
    god->cols = (unsigned int) ft_atoi(db_get(db, "x"));
    god->rows  = (unsigned int) ft_atoi(db_get(db, "y"));
    god->pathwalln = db_get(db, "NO");
    god->pathwalle = db_get(db, "SO");
    god->pathwalls = db_get(db, "WE");
    god->pathwallw = db_get(db, "EA");
    f_find_and_define_player(god, map, 0, 0);
    set_colors(god, colors);
    init_mlx_stuff(god);
    return (true);
}
