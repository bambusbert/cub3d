#include "../inc/f_parsing.h"

char **free_stefan(char **stefan);
char **f_for_stefan(char *s,int k, int x, int y);
void set_stefan(char *dest, char *src);

bool for_fortnite_and_stefan(t_db *db, t_color *colors)
{
    const char *s;
    char **for_stefan;
    int x;
    int y;
    bool ret;

    ret = true;
    s = db_get(db,"TESTMAP");
    x = f_atoll((char *)db_get(db, "x"));
    y = f_atoll((char *)db_get(db, "y"));
    for_stefan = f_for_stefan((char *)s, 0, x, y);
    if (!for_stefan)
      return (false);
    ret = f_from_stefan(db, for_stefan, colors);
    //main2(1, "hallo");
   for_stefan = free_stefan(for_stefan);
    return(ret);
}

char **free_stefan(char **stefan)
{
    int i;

    i = 0;
    while (stefan[i])
    {
        free(stefan[i]);
        i++;
    }
    free(stefan);
    return(NULL);
}

char **f_for_stefan(char *s,int k, int x, int y)
{
    char **for_stefan;
    int i;
    int j;

    i = 0;
    for_stefan = ft_calloc(sizeof(char *), y + 1);
    if (!for_stefan)
        return (printf("Error\nAllocation."), NULL);
    while (i < y)
    {
        for_stefan[i] = ft_calloc(sizeof(char), x + 1);
        if (!for_stefan[i])
            return (printf("Error\nAllocation."), free_stefan(for_stefan));
        j = 0;
        while (j < x)
        {
            // if (s[k] == 32)
            //     for_stefan[i][j] = '1'; TODO delete
            // else
            //     for_stefan[i][j] = s[k];
            set_stefan(&for_stefan[i][j], &s[k]);
            j++;
            k++;
        }
        i++;
    }
    return (for_stefan);
}

void set_stefan(char *dest, char *src)
{
    if (*src == 32)
        *dest = '1';
    else
        *dest = *src;
}
