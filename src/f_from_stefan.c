#include "../inc/f_parsing.h"

bool f_from_stefan(t_db *db, char **map, t_color *colors)
{
    t_god *god;

    god = ft_calloc(1, sizeof(t_god));
	if (!god)
		return (printf("Error\ngod struct malloc fail\n"), false);

    god->map = map;
    //god->map = create_sample_map(god);
    god->cols = (unsigned int) ft_atoi(db_get(db, "x"));
    god->rows  = (unsigned int) ft_atoi(db_get(db, "y"));

    printf("cols: %i rows: %i,\n", god->cols, god->rows);

   // exit(2);

    god->pathwalln = db_get(db, "NO");
    god->pathwalle = db_get(db, "SO");
    god->pathwalls = db_get(db, "WE");
    god->pathwallw = db_get(db, "EA");


    
    printf("%c %i,%i,%i\n", colors[0].key, colors[0].r, colors[0].g, colors[0].b);
    printf("%c %i,%i,%i\n\n", colors[1].key, colors[1].r, colors[1].g, colors[1].b);

    
    int i = 0;
    int j;
    while (god->map[i])
    {
        j = 0;
        while (god->map[i][j])
        {
            if (god->map[i][j] == 'N')
            {
                god->map[i][j] = '2';
                //god->player_angle = 0;
                god->player_start_direction = NORTH;
                break;
            }
            else if (god->map[i][j] == 'E')
            {
                god->map[i][j] = '2';
                god->player_start_direction = EAST;
                //god->player_angle = PI / 2;
                break;
            }
            else if (god->map[i][j] == 'S')
            {
                god->map[i][j] = '2';
                god->player_start_direction = SOUTH;
               // god->player_angle = PI;
                break;
            }
            else if (god->map[i][j] == 'W')
            {
                god->map[i][j] = '2';
                god->player_start_direction = WEST;
                //god->player_angle = 3 * PI / 2;
                break;
            }
            j++;
        }
        if (god->map[i][j] == '2')
            break;
        i++;
    }
    god->player_x = (float) j;
    god->player_y = (float) i;

    i = 0;
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

    printf("x%i\n\ny%i\n\n", j, i);
    printf("%f\n\n%f\n\n", god->player_x, god->player_y);
    god->db = db;
    init_mlx_stuff(god);
    return (true);
}
