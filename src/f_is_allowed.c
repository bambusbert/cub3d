#include "f_parsing.h"

// bool is_allowed(char c)
// {
//     return (c == 'N'|| c == 'O'|| c == 'S' || c == 'W' || c == '0' || c == '1' || c == 32 || c == '\n');
// }


bool is_allowed(char c, t_read_map *m)
{
    if (c == 'N')
        m->n++;
    else if (c == 'E')
        m->o++;
    else if (c == 'S')
        m->s++;
    else if (c == 'W')
        m->w++;
    return (c == 'N'|| c == 'E'|| c == 'S' || c == 'W' || c == '0' || c == '1' || c == 32 || c == '\n');
}

// lass uns das hier anpassen 