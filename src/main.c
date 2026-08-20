#include "f_parsing.h"

int freeturn(char *file, t_db *db, int ret);
bool for_fortnite_and_stefan(t_db *db,t_color *colors);

int main (int ac, char *av[])
{
    char *file;
    t_db db1;
    t_color fc[2];

    file = NULL;
    if (f_test_input(ac, av[1]) == false)
        return (1);
    if (f_read_file(&file, av[1]) == false)
        return (1);
    if (db_init(&db1, 1, 1) == false)
        return (1);
    if (f_parse_into_db(&db1, file) == false)
        return(freeturn(file, &db1, 1));
    if (db1.hmap_size != 7)
        return (ft_putstr_fd("Error\nToo many keys.\n", 2), freeturn(file, &db1, 1));
    f_init_colors(fc);
    if (f_parse_colors(&db1, fc) == false)
        return(freeturn(file, &db1, 1));
    if (f_parse_map(&db1) == false)
        return(freeturn(file, &db1, 1));
    free(file);
    for_fortnite_and_stefan(&db1, fc);
    
    return (freeturn(file, &db1, 0));
}

int freeturn(char *file, t_db *db, int ret)
{
    if (file != NULL)
        free (file);
    if (db != NULL)
        free_db(db);
    return (ret);
}
