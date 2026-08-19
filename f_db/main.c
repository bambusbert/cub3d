#include "f_db.h"

void f_print_db(t_db *db);
void f_fill_db(t_db *db);

int main (void)
{
    t_db db1;
    db_init(&db1, 1, 1);
    printf("%i\n", db1.hmap_cap);
    printf("%i\n", db1.arena_cap);
    db_set(&db1, "Name", "Frido");
    printf("%i\n", db1.hmap_cap);
    printf("%i\n", db1.arena_cap);
    db_set(&db1, "Surame", "Odirf");
    printf("%i\n", db1.hmap_cap);
    printf("%i\n", db1.arena_cap);
    db_set(&db1, "Age", "42");
    printf("%i\n", db1.hmap_cap);
    printf("%i\n", db1.arena_cap);
    db_set(&db1, "Height", "167");
    printf("%i\n", db1.hmap_cap);
    printf("%i\n", db1.arena_cap);
    db_set(&db1, "Job", "No");
    printf("%i\n", db1.hmap_cap);
    printf("%i\n", db1.arena_cap);
    db_set(&db1, "Hobby", "Tabletennis");
    printf("%i\n", db1.hmap_cap);
    printf("%i\n", db1.arena_cap);
    printf("%s\n", db_get(&db1, "Name"));
    free_db(&db1);
    return (0);
}

void f_fill_db(t_db *db)
{
    uint16_t i;

    i = 0;
    while (i < 600)
    {
        db->data_arena[i] = 48;
        db->arena_head = i;
        i++;
    }
}

void f_print_db(t_db *db)
{
    uint16_t i;

    i = 0;
    while (i < db->arena_head)
    {
        write(1, &db->data_arena[i], 1);
        i++;
    }
    write(1, "\n", 1);
}
