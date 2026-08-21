- check if i need aurorepeaton / -off
- forbidden functions (bash -c "$(curl -fsSL https://raw.githubusercontent.com/beistvan/mandatory_cub3d_forbidden_functions_checker/main/mandatory_cub3d_forbidden_functions_checker.sh)")
  abs
  memcpy - static const variable calls memcpy implicitly
  strcmp




VETSATESTA
- nl_between_info.cub geht ned
- arthurs big map segfaults (very likely because of stack overflow in recursive flood fill)
-


other testers
42_cub_tester
cub3D_map_tester
cub3d-tester

mem sanituyer, leak sanitiyer, undef b sanitizer, adress sanitizer flags
long ass number in map
stack overflow recursion
