*This project has been created as part of the 42 curriculum by slambert, fsitter.*

# cub3D

This project is a Wolfenstein 3D-inspired ray-casting engine built from scratch in C using minilibx.

## Description

cub3D renders a real-time, first-person 3D view of a 2D maze using ray-casting, the same family of techniques that powered Wolfenstein 3D. Given a `.cub` scene file describing a map, four wall textures and floor/ceiling colors, the program opens a window (via miniLibX) and lets you walk and look around the maze in real time.

The core of the project is:
- A **parser** that reads a `.cub` file, validates its syntax, and stores the scene elements (textures, colors, map) in a small custom hashmap/arena-backed key-value store (`f_db`) before turning the grid into a playable map.
- A **ray-caster** using Digital Differential Analysis (DDA) to cast one ray per screen column, find the nearest wall, and pick the correct texture based on which face (N/S/E/W) was hit. The hight of the wall per ray cast is inversely proportional to the length of the ray (after fisheye correction has been applied)
- An **event-driven game loop** built on miniLibX hooks for keyboard/mouse input, per-frame movement, and rendering.

### Features

Mandatory part:
- Parses and validates `.cub` scene files (textures, floor/ceiling colors, and the map itself), rejecting malformed input with `Error\n` and a dedicated error message on stderr.
- Real-time 3D rendering of the maze from a first-person perspective.
- Per-wall-side textures (North/South/East/West) loaded from the paths given in the scene file.
- Configurable floor and ceiling colors via their RGB colors.
- Smooth keyboard-driven movement and looking around.
- Clean shutdown on `ESC` or when the window is closed.

Bonus part implemented:
- Wall collisions.
- A 2D minimap with a field-of-view cone, rendered live in a corner of the window.
- Mouse-look — rotate the camera by moving the mouse.

## Controls

| Key | Action |
| --- | --- |
| `W` / `A` / `S` / `D` | Move forward / left / backward / right |
| `←` / `→` | Turn (look) left / right |
| Mouse | Turn (look) left / right |
| `ESC` | Close the window and quit |
| cross (window frame) | Close the window and quit |

## What is considered a valid map?
A valid map has to respect these rules:
- consists ONLY of these characters: 1, 0, N, E, S, W, Space
    - 1 represents a wall
    - 0 represents an empty space
    - N/E/S/W represents the player, the letter indicates the direction the player looks initially
- there has to be exactly one player
- the map around the player has to be fully surrounded by walls
- spaces will be interpreted as empty fields during parsing. if that results in a valid map they are converted to walls
- maps must not have empty (new) lines between other parts of the map (they will not be skipped)


The playable map is considered the area in which the player can walk onto. The playable map can be a part of the actual map, it can also be the full map.

A simple valid map is:
```
111111
100101
101001
1100N1
111111
```

another valid map (playable map is fully surrounded by walls)
```
111011
100101
101001
1100N1
111111
```

another valid map:
```
    1
   101
  1001
 100N1
111111
```
We chose that approach because the reason for the map needing to be surrounded by walls is so 1)  that no ray cast travels and 2) no player walks out of bounds, which would result in a segfault. We ensure that this is not going to happen by forcing the player to be surrounded by walls (playable map). Additionally we are fencing the full map off by an additional layer of 1s (wall character) once the map is validated.

## The `.cub` scene format

The program takes a single argument: the path to a scene description file ending in `.cub`. This is an example of a valid `.cub` file. The `.cub` file must not be hidden.

```
NO ./sprites/wall_n.xpm
SO ./sprites/wall_s.xpm
WE ./sprites/wall_w.xpm
EA ./sprites/wall_e.xpm
F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```

- `NO` / `SO` / `WE` / `EA` — paths to the North/South/West/East wall textures. The texture files (sprites) can not be hidden.
- `F` / `C` — floor / ceiling color as `R,G,B` (0–255). There must be no additional characters in these lines - but spaces.
- The map is made of `0` (empty space), `1` (wall) and `N`/`S`/`E`/`W` (the player's starting position and facing direction), spaces are a valid part of the map. The map must be the last element in the file. More information about the map can be found in chapter `What is considered a valid map?`.

Sample maps (valid and invalid) are available in [`dotcubs/`](./dotcubs).

The validation of the map happens recursively if the map fits in the stack for efficiency reasons. If the map does not fit in the stack the validation happens in a non-recursive way. Otherwise we would produce a stack overflow, which would result in a segfault.

## Instructions

### Requirements

- A Linux (or macOS) environment with `cc`, `make`, and the X11 development headers.
- [MiniLibX](https://github.com/42Paris/minilibx-linux) installed on the system (`libmlx`, `libXext`, `libX11`).

### Compilation

```bash
make        # builds the mandatory part -> ./cub3D
make bonus  # builds the bonus part. It does exactly the same as make. It is required by the subject to have a bonus rule.
make clean  # removes object files
make fclean # removes object files and the binary
make re     # fclean + all
```

The Makefile also builds `libft` from its own sources/Makefile before linking it into the project.

### Running

```bash
./cub3D <path/to/map.cub>
```

For example:

```bash
./cub3D dotcubs/hello.cub
```

If the map or any referenced texture is invalid, the program prints `Error` followed by an explanatory message on stderr and exits without opening a window.

## Project structure

```
src/           game loop, rendering, movement, input, bonus features
inc/           cub3d.h / f_parsing.h — shared types, constants and prototypes
f_db/          a single allocation append only in memory database with an index hashmap (no pointers) to set and retrive data
f_file_reader/ a max efficency file-reading tool used by the parser
libft/         42 libft, built as a library and linked into the project
sprites/       default wall textures used by the sample maps
dotcubs/       sample .cub scene files
```

## Resources

- [Lodev's Raycasting tutorial](https://lodev.org/cgtutor/raycasting.html) — the classic reference for grid-based ray-casting and the DDA algorithm used here.
- [MiniLibX documentation / 42Paris minilibx-linux](https://harm-smits.github.io/42docs/libs/minilibx) — the graphics library used to open the window, draw pixels and handle events.
- [Digital Differential Analyzer (Wikipedia)](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)) — background on the line-stepping algorithm used to cast rays.
- The original [Wolfenstein 3D](http://users.atw.hu/wolf3d/) as the project's reference game.
- [Make Your Own Raycaster Part 1 by 3DSage](https://www.youtube.com/watch?v=gYRrGTC7GtA)
- [Make Your Own Raycaster Part 2 by 3DSage](https://www.youtube.com/watch?v=PC1RaETIx3Y)
- [DDA Raycasting algorithm by kitrofimov](https://www.youtube.com/watch?v=IDmWuSrEkow)

- [`Cub3D_tester` by VestaManuyko](https://github.com/VestaManuyko/Cub3D_tester) — the external test suite used to validate the parser against valid/invalid maps. Our interpretation of what is to be considered a valid map differs in some cases though.

**AI usage:** The first version of this README was drafted with the help of Claude and was heavily edited afterwards. AI was used as a sparring partner to discuss Ideas. No AI was used to write code.