TODO:

- gleiches problem bei invalid::blank_line_in_map
- printf weg (2)
- nl_between_info.cub geht ned (weil spaces nach sprite: "SO         ./sprites/wall_s.xpm   ")

- funcheck error
┏ Aborted 
┗━┳━━ free_db at ./f_db/f_db_init.c:79:3 (0x403d27)
  ┗━┳━━ cleanup_and_return at src/main.c:54:3 (0x4014ba)
    ┗━━━━ main at src/main.c:31:14 (0x401362)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_calloc at ft_calloc.c:31:8 (0x40705f)
  ┗━┳━━ allocate_slots at ./f_db/f_db_init.c:60:16 (0x403dd7)
    ┗━┳━━ hashmap_init at ./f_db/f_db_init.c:36:6 (0x403c36)
      ┗━┳━━ db_init at ./f_db/f_db_init.c:20:6 (0x403b7d)
        ┗━━━━ main at src/main.c:30:6 (0x401342)


other testers
42_cub_tester
cub3D_map_tester
cub3d-tester

mem sanituzer, leak sanitizer, undef b sanitizer, adress sanitizer flags
long ass number in map


- forbidden functions (bash -c "$(curl -fsSL https://raw.githubusercontent.com/beistvan/mandatory_cub3d_forbidden_functions_checker/main/mandatory_cub3d_forbidden_functions_checker.sh)")
