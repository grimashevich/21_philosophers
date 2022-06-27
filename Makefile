NAME := philo
CC := cc
OBJ_DIR := obj

CFLAGS := -Wall -Wextra -Werror -g
CPPFLAGS := -MMD
# S_FLAGS := -fsanitize=address
S_FLAGS = -fsanitize=thread
			
SRC := 	main.c		common01.c	philo01.c	philo02.c	\
		ft_atoi.c	common02.c

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
