NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra
INC = ./inc

SRC = src/*.c

all:
	$(CC) $(CFLAGS) -I $(INC) $(SRC) -o $(NAME)

TEST_ARGS_1 = 1 2 3 4 5
test_1: all
	./$(NAME) $(TEST_ARGS_1)

TEST_ARGS_2 = 1 2 3 4 -5
test_2: all
	./$(NAME) $(TEST_ARGS_2)

TEST_ARGS_3 = 1 2 3 4 a5
test_3: all
	./$(NAME) $(TEST_ARGS_3)

PHONY: all clean fclean re
