NAME        = db
CC         = cc
CFLAGS    = -Wall -Wextra -Werror
DFLAGS      = -MMD -MP
RM          = rm -f

SRC         = main.c \
              f_db_init.c \
              f_db_hash.c \
              f_db_resize.c \
              f_db_set_get.c

OBJ_DIR     = obj

OBJ         = $(SRC:%.c=$(OBJ_DIR)/%.o)
DEP         = $(SRC:%.c=$(OBJ_DIR)/%.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) ../libft/libft.a -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

-include $(DEP)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re