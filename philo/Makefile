NAME = philo

# https://nafuka11.github.io/philosophers-visualizer/

CC = cc
CFLAGS = -Wall -Werror -Wextra
SANITIZE = -fsanitize=thread
INC = ./inc
DEBUGFLAGS = -D DEBUG=1

SRC_DIR = ./src
SRC = $(SRC_DIR)/*.c
OBJ_DIR = obj

debug:
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -I $(INC) $(SRC) -o $(NAME)

all:
	$(CC) $(CFLAGS) -I $(INC) $(SRC) -o $(NAME)

clean:

fclean:

re:

PHONY: all clean fclean re

# special modes
sanitize:
	$(CC) $(CFLAGS) $(SANITIZE) -I $(INC) $(SRC) -o $(NAME)

unit_tests:
	@echo "---------------------------------------------------------------"
	@echo "*                          UNIT TESTS                         *"
	@echo "---------------------------------------------------------------"
	@cc tests/tests_parsing.c $(shell find src -name '*.c' ! -name 'main.c') -I $(INC) -o unit_tests && ./unit_tests
	rm unit_tests

TEST_ARGS_1 = 1 2 3 4 5
test_1: all
	./$(NAME) $(TEST_ARGS_1)

TEST_ARGS_2 = 1 2 3 4 -5
test_2: all
	./$(NAME) $(TEST_ARGS_2)

TEST_ARGS_3 = 1 2 3 4 a5
test_3: all
	./$(NAME) $(TEST_ARGS_3)

