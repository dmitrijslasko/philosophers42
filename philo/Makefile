GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

NAME = philo

# VISUALIZER URL
# https://nafuka11.github.io/philosophers-visualizer/

CC = cc
CFLAGS = -Wall -Werror -Wextra
INC = ./inc

DEBUGFLAGS = -Wall -Werror -Wextra -g -D DEBUG=1
SANITIZE = -fsanitize=thread

SRC_DIR = ./src/
OBJ_DIR = ./obj/

SRC = $(wildcard $(SRC_DIR)*.c) $(wildcard $(SRC_DIR)**/*.c)
OBJ = $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\n$(GREEN)$(NAME) got successfully compiled.$(RESET)"


$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@
	@echo "$(GREEN)%%%%$(RESET)\c"

clean:
	@rm -f $(OBJ_DIR)**/*.o
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)clean complete\n$(RESET)\c"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)fclean complete\n$(RESET)\c"

re: fclean all

# special modes
debug:
	$(CC) $(DEBUGFLAGS) -I $(INC) $(SRC) -o $(NAME)

sanitize:
	$(CC) $(CFLAGS) $(SANITIZE) -I $(INC) $(SRC) -o $(NAME)

unit_tests:
	@echo "---------------------------------------------------------------"
	@echo "*                          UNIT TESTS                         *"
	@echo "---------------------------------------------------------------"
	@cc tests/tests_parsing.c $(shell find src -name '*.c' ! -name 'main.c') -I $(INC) -o unit_tests && ./unit_tests
	rm unit_tests

.PHONY: all clean fclean re debug sanitize unit_tests