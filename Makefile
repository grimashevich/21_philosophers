NAME := philo
CC := clang
OBJ_DIR := obj

CFLAGS := -Wall -Wextra -Werror -g
CPPFLAGS := -MMD
S_FLAGS := -fsanitize=address
			
SRC := 	main.c

OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)

DEP := $(OBJ:.o=.d)

.PHONY: all clean fclean re bonus

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) $(S_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(S_FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

-include $(DEP)

clean:
	@rm -f $(OBJ) $(DEP)

fclean: clean
	@rm -f $(NAME)

re: fclean all
