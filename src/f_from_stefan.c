#include "../inc/f_parsing.h"

bool f_from_stefan(t_db *db, char **map, t_color *colors)
{
    t_god *god;

    god = ft_calloc(1, sizeof(t_god));
	if (!god)
		return (printf("Error\ngod struct malloc fail\n"), false);

    god->map = map;
    god->cols = (unsigned int) ft_atoi(db_get(db, "x"));
    god->rows  = (unsigned int) ft_atoi(db_get(db, "y"));
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
                god->player_angle = 0;
                break;
            }
            else if (god->map[i][j] == 'E')
            {
                god->player_angle = PI / 2;
                break;
            }
            else if (god->map[i][j] == 'S')
            {
                god->player_angle = PI;
                break;
            }
            else if (god->map[i][j] == 'W')
            {
                god->player_angle = 3 * PI / 2;
                break;
            }
            j++;
        }
        i++;
    }
    god->player_x = i;
    god->player_y = j;

    printf("x%i\n\ny%i\n\n", i, j);
    printf("%i\n\n%i\n\n", god->player_x, god->player_y);
    init_mlx_stuff(god);
    return (true);
}
