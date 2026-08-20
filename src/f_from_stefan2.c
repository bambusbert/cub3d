#include "../inc/f_parsing.h"

enum e_direction f_define_player_direction(char c);

void f_find_and_define_player(t_god *god, char **m, int i, int j)
{
    while (m[i])
    {
        j = 0;
        while (m[i][j])
        {
            if (m[i][j] == 'N' || m[i][j] == 'E' || m[i][j] == 'S' || m[i][j] == 'W')
            {
                god->player_start_direction = f_define_player_direction(m[i][j]);
                m[i][j] = '2';
                god->player_x = (float) j + 0.5;
                god->player_y = (float) i + 0.5;
                return ;
            }
            j++;
        }
        i++;
    }
}

enum e_direction f_define_player_direction(char c)
{
    if (c == 'N')
        return (NORTH);
    else if (c == 'E')
        return (EAST);
    else if (c == 'S')
        return (SOUTH);
    else if (c == 'W')
        return (WEST);
    return NULL;
}

bool f_from_stefan2(t_db *db, char **map, t_color *colors)
{
    t_god *god;

    god = ft_calloc(1, sizeof(t_god));
	if (!god)
		return (printf("Error\ngod struct malloc fail\n"), false);
    god->db = db;
    god->map = map;
    god->cols = (unsigned int) ft_atoi(db_get(db, "x"));
    god->rows  = (unsigned int) ft_atoi(db_get(db, "y"));
    god->pathwalln = db_get(db, "NO");
    god->pathwalle = db_get(db, "SO");
    god->pathwalls = db_get(db, "WE");
    god->pathwallw = db_get(db, "EA");

    f_find_and_define_player(god, map, 0, 0);

    //return (true);
    ///TODO hier noch colors dann -48 loeschen oder in function
    printf("%c %i,%i,%i\n", colors[0].key, colors[0].r, colors[0].g, colors[0].b);
    printf("%c %i,%i,%i\n\n", colors[1].key, colors[1].r, colors[1].g, colors[1].b);





    int i = 0;
    int j;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            map[i][j] -= 48;
            printf("%c\n", map[i][j] + 48);
            j++;
        }
        //printf("%s\n", map[i]);
        i++;
    }
    //exit(2);

    //TODO set god->color_ceiling & god->color_floor
    god->color_ceiling = 0;
    god->color_floor = 0;
    init_mlx_stuff(god);
    return (true);
}
