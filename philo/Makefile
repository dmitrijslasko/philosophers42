GREEN = \033[0;32m
RED = \033[0;31m
RST = \033[0m

NAME = philo

# VISUALIZER URL
# https://nafuka11.github.io/philosophers-visualizer/

CC = cc
INC = ./inc

CFLAGS = -Wall -Werror -Wextra
DEBUGFLAGS = -Wall -Werror -Wextra -g -D DEBUG=1
SANITIZE = -fsanitize=thread

SRC_DIR = ./src/
OBJ_DIR = ./obj/

SRC = $(wildcard $(SRC_DIR)*.c) $(wildcard $(SRC_DIR)**/*.c)
OBJ = $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\n$(GREEN)$(NAME) got successfully compiled.$(RST)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@
	@echo "$(GREEN)%%%%$(RST)\c"

clean:
	@rm -f $(OBJ_DIR)**/*.o
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)clean complete\n$(RST)\c"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)fclean complete\n$(RST)\c"

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

# Helgrind launch
HELGRIND = valgrind --tool=helgrind --log-file=helgrind.log

# Argument sets (last argument is expected outcome: 1 = should die, 0 = should not die)
ARGS_LIST = 	"1 800 200 200 10 1"	\
\
				"2 80 20 20 10 0"	\
				"4 80 20 20 10 0"	\
				"5 80 20 20 10 0"	\
\
				"2 800 200 200 10 0"	\
				"4 800 200 200 10 0"	\
				"5 800 200 200 10 0"	\
				"10 800 200 200 10 0"	\
				"20 800 200 200 10 0"	\
				"50 800 200 200 10 0"	\
				"100 800 200 200 10 0"	\
				"200 800 200 200 10 0"	\
				"500 800 200 200 10 0"	\
				"10 399 200 200 10 1"	\
				"2 399 200 200 10 1"	\
				"5 599 200 200 10 1"	\
				"10 210 100 100 5 0"	\
				"5 150 60 60 5 1"	\
				"4 120 50 50 3 0"	\
				"3 120 60 60 3 1"	\
				"10 100 40 40 5 0"	\
				"10 80 30 30 5 0"	\
				"300 1000 100 100 10 0"	\
				"400 1200 200 200 10 0"	\
				"500 1500 200 200 10 0"

define run_test
	> test_log.log; \
	echo "\nTesting with ARGS: $(1)" | tee -a test_log.log; \
	ARGS=$$(echo $(1) | awk '{print $$1, $$2, $$3, $$4, $$5}'); \
	EXPECTED_OUTCOME=$$(echo $(1) | awk '{print $$NF}'); \
	./$(NAME) $$ARGS >> test_log.log 2>&1; \
	\
	if grep -iq "died" test_log.log; then \
		echo "❌ Philo died..." | tee -a test_log.log; \
		if [ "$$EXPECTED_OUTCOME" = "1" ]; then \
			echo "✅ Expected outcome: PASS" | tee -a test_log.log; \
		else \
			echo "❌ Unexpected outcome: FAIL" | tee -a test_log.log; \
		fi; \
	else \
		echo "✅ No philos died!" | tee -a test_log.log; \
		if [ "$$EXPECTED_OUTCOME" = "0" ]; then \
			echo "✅ Expected outcome: PASS" | tee -a test_log.log; \
		else \
			echo "❌ Unexpected outcome: FAIL" | tee -a test_log.log; \
		fi; \
	fi; \
	echo "-----------------------------------------------------" | tee -a test_log.log
endef

# Run Helgrind test and save full output
define run_helgrind_test
	echo "\nTesting with ARGS: $(1)" | tee -a helgrind.log; \
	$(HELGRIND) ./$(NAME) $(1) >> helgrind.log 2>&1; \
	echo "-----------------------------------------------------" | tee -a helgrind.log; \
	grep -i "possible data race" helgrind.log && echo "❌ Data Race Detected!" || echo "✅ No data race found"; \
	grep -i "lock order violation" helgrind.log && echo "❌ Lock Order Violation Detected!" || echo "✅ No lock order violations"; \
	grep -i "potential deadlock" helgrind.log && echo "❌ Potential Deadlock Detected!" || echo "✅ No deadlocks detected"; \
	grep -i "mutex" helgrind.log && echo "❌ Mutex Misuse Detected!" || echo "✅ Mutexes handled properly"; \
	grep -i "died" helgrind.log && echo "❌ Philo died..." || echo "✅ No philos died!"; \
	echo "-----------------------------------------------------" | tee -a helgrind.log
endef

tests: re
	@echo "Running Tests..." > helgrind.log; \
	SUCCESS=0; FAIL=0; COUNT=0; \
	for args in $(ARGS_LIST); do \
		COUNT=$$((COUNT+1)); \
		echo "\nRunning test $$COUNT: ARGS=$$args" | tee -a helgrind.log; \
		$(call run_test, $$args); \
		\
		if tail -n 5 test_log.log | grep -iq "Unexpected outcome: FAIL"; then \
			FAIL=$$((FAIL+1)); \
		else \
			SUCCESS=$$((SUCCESS+1)); \
		fi; \
	done; \
	echo "\n==== TEST SUMMARY ====" | tee -a helgrind.log; \
	echo "Total Tests: $$TOTAL" | tee -a helgrind.log; \
	echo "✅ Success: $$SUCCESS" | tee -a helgrind.log; \
	echo "❌ Failed: $$FAIL" | tee -a helgrind.log; \
	echo "======================" | tee -a helgrind.log


helgrind_tests: re
	@echo "Running Helgrind Tests..." > helgrind.log; \
	for args in $(ARGS_LIST); do \
		$(call run_helgrind_test, $$args); \
	done


.PHONY: all clean fclean re debug sanitize unit_tests tests helgrind_tests
