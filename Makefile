# Project name
NAME = cub3d
NAME_BONUS = cub3d_bonus

# Suppress directory change
MAKEFLAGS += --no-print-directory

# Colours
GREEN = \033[0;32m
RED = \033[0;31m

# Compiler and flags
CC = cc
#CFLAGS = -Wall -Wextra -Werror -g
CFLAGS = -g
INCLUDES = -I./inc

# libft
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBS = -L$(LIBFT_PATH) -lft

# MinilibX flags
MLX_FLAGS = -lmlx -lXext -lX11 -lm

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRC =	src/cub3d.c \
		src/cleanup.c \
		src/input_handling.c \
		src/debug.c \
		src/init_main.c \
		src/init_textures.c \
		src/helper.c \
		src/draw_main.c \
		src/draw_helper.c \
		src/movement.c \
		src/dda.c \
		src/dda_init.c

BONUS_SRC = src/bonus.c

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
BONUS_OBJS =$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(BONUS_SRC))
HEAD = inc/cub3d.h

# Rules
all: $(NAME)

#TODO libft dependency
$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) Compiled successfully!"

bonus: $(LIBFT) $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(BONUS_OBJS) $(LIBS) $(MLX_FLAGS) -o $(NAME_BONUS)
	@echo "$(GREEN)✅ $(NAME_BONUS) Compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEAD)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)🧹 Object files removed!"

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "$(RED)🧹 Executable(s) removed!"

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug bonus