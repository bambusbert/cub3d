#include "../inc/f_parsing.h"
#include <fcntl.h>

void f_init_rm(t_db *db, t_read_map *m);
bool f_map_to_file(t_read_map *m);
void f_measure_map(t_read_map *m);
void f_cut_nl(t_read_map *m);

bool f_parse_map(t_db *db)
{
    t_read_map m;
    char *x;
    char *y;
    
    f_init_rm(db, &m);
    if (f_map_to_file(&m) == false)
        return (false);
    f_measure_map(&m);
    if (f_test_map(db, &m) == false)
        return (false);
    x = ft_itoa(m.xmax + 2);
    if (!x)
        return (ft_putstr_fd("Error\nAllocation.\n", 2), false);
    if (db_set(db, "x", x) == false)
        return (false);
    free(x);
    y = ft_itoa(m.y + 2);
    if (!y)
        return (ft_putstr_fd("Error\nAllocation.\n", 2),false);
    if (db_set(db, "y", y) == false)
        return (false);
    free(y);
    return (true);
}

void f_init_rm(t_db *db, t_read_map *m) // todo bool machen und db get NULL sichern??? muss ich nicht weil map fuer valid mit 1 oder 0 beginnen muss
{
    ft_bzero(m, sizeof(*m));
    m->y = 1;
    m->x = 1;
    m->map = db_get(db, "MAP");
}

bool f_map_to_file(t_read_map *m)
{
    bool ret;
    
    ret = true;
    while (m->map[m->i])
    {
        if (!is_allowed(m->map[m->i], m))
            return (ft_putstr_fd("Error\nWrong Sign.\n", 2), close(m->fd), false);
        m->i++;
    }
    if (m->n + m->o + m->s + m->w > 1)
    {
        ret = false;
        ft_putstr_fd("Error\ntoo many players\n", 2);
    }
    close(m->fd);
    return (ret);
}


void f_measure_map(t_read_map *m)
{
    m->i = 0;
    while (m->map[m->i])
    {
        if (m->map[m->i] == '\n')
        {
            m->x--;
            if (m->x > m->xmax)
                m->xmax = m->x;
            m->y++;
            m->x = 0;
        }
        m->i++;
        m->x++;
    }
    m->x--;
    if (m->x > m->xmax)
        m->xmax = m->x;
    if (m->y == 1)
        m->xmax = m->i;
    m->i--;
    f_cut_nl(m);
}

void f_cut_nl(t_read_map *m)
{
    while (m->map[m->i] == '\n')
    {
        m->y--;
        m->i--;
    }
}


/*
 * 
 * durch die ganze map gehen und checken if nciht erlaubtes sign - check *
 * in ein file schreiben - check * 
 * jetzt buffer anlegen mit (x + 2 * y + 2) dann memset(buffer, 32); *
 * dann bei x1 x1 beginnen zu fuellen - check :D *
 * f_parse_map2.c in 25 zeilencode umwandeln - check *
 * f_parse_map.c 5 funktionen also eine ins 2er file geben - check *
 * checken ob player nur 1 mal da ist - check *
 * 
 * 
 *  * schauen wo ich floodfill machen kann ich kann ja bei dbget nicht weil constchar done ** check ***
 *  * floodill machen auf 1d also in buffer floodfill machen nach dem db set gemacht wurde **done check**
 * 
 * HIER SIND WIR:
 * daten fuer die stefan brauch in db einfuegen
 * 
 * 
 * eventuell struct mit keys und bool setzten wenn ich sie einfuege als gefuellt oder sagen append geht
 * 
 * 
 * 
 * 
 */