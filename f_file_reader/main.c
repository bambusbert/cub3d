#include "f_read_file.h"

int main (int ac, char *av[])
{
    char *file;
    if (ac != 2)
        return (-1);
    
    file = f_read_file(av[1]);
    if (!file)
        return (-1);
    ft_printf("%s\n", file);
    free (file);
    return (0);
}
