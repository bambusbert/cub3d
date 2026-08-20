#include "../inc/f_parsing.h"

bool f_allocate_test_map(t_read_map *m);
void f_fill_test_map(t_read_map *m);
int f_find_player(const char *s);

void print_map(t_db *db, t_read_map *m); //todo loeschen


int f_find_player(const char *s)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == 'N' || s[i] == 'E' || s[i] == 'S' || s[i] == 'W')
            return (i);
        i++;
    }
    return (-1);
}

bool f_flood_that_shi(char *s, int start, int ll, t_db *db, t_read_map *m)
{
    bool ret;
    ret = true;
    if (s[start] == 32)
        return (false);
    else if (s[start] == WALL_CHAR || s[start] == 'x')
        return (true);
    s[start] = 'x';
    
    ret = f_flood_that_shi(s, start - 1, ll, db, m);
    if (ret == false)
        return (false);
    ret = f_flood_that_shi(s, start + 1, ll, db, m);
    if (ret == false)
        return (false);
    ret = f_flood_that_shi(s, start - ll, ll, db, m);
    if (ret == false)
        return (false);
    ret = f_flood_that_shi(s, start + ll, ll, db, m);
    if (ret == false)
        return (false);
    return (true);
}


bool f_test_map(t_db *db, t_read_map *m)
{
    if (f_allocate_test_map(m) == false)
        return (false);
    f_fill_test_map(m);
    if (db_set(db, "TESTMAP", m->buffer) == false)
       return(free(m->buffer), false);
    m->pp = f_find_player(m->buffer);
    if (m->pp == -1)
        return(printf("Error\nNo Player."), free(m->buffer), false);
    if (f_flood_that_shi(m->buffer, m->pp, m->xmax + 2, db, m) == false)
        return(printf("Error\nMap wrong."), free(m->buffer), false);
    free(m->buffer);
    return (true);
}

void f_fill_test_map(t_read_map *m)
{
    while (m->map[m->i])
    {
        if (m->map[m->i] == '\n')
        {
            m->i++;
            while (m->k < m->xmax + 2)
            {
                m->j++;
                m->k++;
            }
            m->k = 0;
        }
        else
        {
            m->buffer[m->j] = m->map[m->i];
            m->i++;
            m->j++;
            m->k++;
        }
    }
}

bool f_allocate_test_map(t_read_map *m)
{
    m->mapsize = (m->xmax + 2) * (m->y + 2);
    m->buffer = ft_calloc(sizeof(char) ,(m->mapsize + 1));
    if (!m->buffer)
        return (printf("Error\nAllocation."), false);
    ft_memset(m->buffer, ' ', m->mapsize);
    m->i = 0;
    m->j = 1 + m->xmax + 2;
    return (true);
}


// void print_map(t_db *db, t_read_map *m)
// {

    
//     int s = 0;
//     int h = 0;    
//     // print 1 ori im buffer
//     while (m->buffer[s])
//     {
//         while (h < m->xmax + 2)
//         {
//             printf("%c", m->buffer[s]);
//             h++;
//             s++;
//         }
//         h = 0;
//         printf("\n");
//     }
//     const char *suwi = db_get(db, "TESTMAP");
//     if (suwi[0] == 32)
//         printf("\n");
//     // printf("\n");
//     // printf("\n");
//     // printf("\n");
//     // s = 0;
//     // h = 0;
//     // //print 2 aus db
//     // while (suwi[s])
//     // {
//     //     while (h < m->xmax + 2)
//     //     {
//     //         printf("%c", suwi[s]);
//     //         h++;
//     //         s++;
//     //     }
//     //     h = 0;
//     //     printf("\n");
//     // }
//     // print 3 so ist es in db
//     // printf("\n%s\n\n\n", db_get(db, "MAP"));
    
//     // printf("\n%s\n\n\n\n", suwi);
    
// }
