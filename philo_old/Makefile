include config.mk

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

.DEFAULT_GOAL := all

all: $(NAME) $(HEADER_FILE)

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
	@echo "$(YELLOW)clean complete\n$(RST)\c"

fclean: clean
	@rm -f $(NAME) $(HEADER_FILE)
	@echo "$(YELLOW)fclean complete\n$(RST)\c"
	@rm -rf ./logs/

re: fclean all

# SPECIAL MODES
# extended output for debugging
debug:
	$(CC) $(DEBUGFLAGS) -I $(INC) $(SRC) -o $(NAME)

# launches with Thread Sanitizer
sanitize:
	$(CC) $(CFLAGS) $(SANITIZE) -I $(INC) $(SRC) -o $(NAME)

# runs some unit tests
unit_tests:
	@echo "---------------------------------------------------------------"
	@echo "*                          UNIT TESTS                         *"
	@echo "---------------------------------------------------------------"
	@cc tests/tests_parsing.c $(shell find src -name '*.c' ! -name 'main.c') -I $(INC) -o unit_tests && ./unit_tests
	rm ./unit_tests

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
	LOGFILE=logs/test_`printf "%02d" $$COUNT`.log; \
	> $$LOGFILE; \
	echo "\nTesting #$$COUNT with ARGS: $(1)" | tee -a $$LOGFILE; \
	ARGS=$$(echo $(1) | awk '{print $$1, $$2, $$3, $$4, $$5}'); \
	EXPECTED_OUTCOME=$$(echo $(1) | awk '{print $$NF}'); \
	./$(NAME) $$ARGS >> $$LOGFILE 2>&1; \
	\
	if grep -iq "died" $$LOGFILE; then \
		echo "❌ Philo died..." | tee -a $$LOGFILE; \
		if [ "$$EXPECTED_OUTCOME" = "1" ]; then \
			echo "✅ Expected outcome: PASS" | tee -a $$LOGFILE; \
		else \
			echo "❌ Unexpected outcome: FAIL" | tee -a $$LOGFILE; \
		fi; \
	else \
		echo "✅ No philos died!" | tee -a $$LOGFILE; \
		if [ "$$EXPECTED_OUTCOME" = "0" ]; then \
			echo "✅ Expected outcome: PASS" | tee -a $$LOGFILE; \
		else \
			echo "❌ Unexpected outcome: FAIL" | tee -a $$LOGFILE; \
		fi; \
	fi; \
	echo "-----------------------------------------------------" | tee -a $$LOGFILE
endef

# Valgrind / Helgrind launch
VALGRIND = valgrind
HELGRIND = valgrind --tool=helgrind

# Run Valgrind test and save full output in a numbered file
define run_valgrind_test
	LOGFILE=logs/valgrind_`printf "%02d" $$COUNT`.log; \
	echo "\nTesting #$$COUNT with ARGS: $(1)" | tee -a $$LOGFILE; \
	ARGS=$$(echo $(1) | awk '{print $$1, $$2, $$3, $$4, $$5}'); \
	$(VALGRIND) --log-file=$$LOGFILE ./$(NAME) $$ARGS >> $$LOGFILE 2>&1; \
	echo "-----------------------------------------------------" | tee -a $$LOGFILE; \
	grep -i "lost" $$LOGFILE && echo "❌ Memory leaks!" || echo "✅ No memory leaks found"; \
	echo "-----------------------------------------------------" | tee -a $$LOGFILE
endef

# Run Helgrind test and save full output in a numbered file
define run_helgrind_test
	LOGFILE=logs/helgrind_`printf "%02d" $$COUNT`.log; \
	echo "\nTesting #$$COUNT with ARGS: $(1)" | tee -a $$LOGFILE; \
	ARGS=$$(echo $(1) | awk '{print $$1, $$2, $$3, $$4, $$5}'); \
	$(HELGRIND) --log-file=$$LOGFILE ./$(NAME) $$ARGS >> $$LOGFILE 2>&1; \
	echo "-----------------------------------------------------" | tee -a $$LOGFILE; \
	grep -i "possible data race" $$LOGFILE && echo "❌ Data Race Detected!" || echo "✅ No data race found"; \
	grep -i "lock order violation" $$LOGFILE && echo "❌ Lock Order Violation Detected!" || echo "✅ No lock order violations"; \
	grep -i "potential deadlock" $$LOGFILE && echo "❌ Potential Deadlock Detected!" || echo "✅ No deadlocks detected"; \
	grep -i "mutex" $$LOGFILE && echo "❌ Mutex Misuse Detected!" || echo "✅ Mutexes handled properly"; \
	echo "-----------------------------------------------------" | tee -a $$LOGFILE
endef


tests: re
	mkdir -p logs
	@echo "Running Tests..." > logs/test_summary.log; \
	SUCCESS=0; FAIL=0; COUNT=0; \
	for args in $(ARGS_LIST); do \
		COUNT=$$((COUNT+1)); \
		$(call run_test, $$args); \
		\
		if tail -n 5 logs/test_`printf "%02d" $$COUNT`.log | grep -iq "Unexpected outcome: FAIL"; then \
			FAIL=$$((FAIL+1)); \
		else \
			SUCCESS=$$((SUCCESS+1)); \
		fi; \
	done; \
	echo "\n==== TEST SUMMARY ====" | tee -a logs/test_summary.log; \
	echo "Total Tests: $$COUNT" | tee -a logs/test_summary.log; \
	echo "✅ Success: $$SUCCESS" | tee -a logs/test_summary.log; \
	echo "❌ Failed: $$FAIL" | tee -a logs/test_summary.log; \
	echo "======================" | tee -a logs/test_summary.log

tests_valgrind: re
	mkdir -p logs
	@echo "Running Valgrind Tests..." > logs/valgrind_summary.log; \
	COUNT=0; \
	for args in $(ARGS_LIST); do \
		COUNT=$$((COUNT+1)); \
		$(call run_valgrind_test, $$args); \
	done

tests_helgrind: re
	mkdir -p logs
	@echo "Running Helgrind Tests..." > logs/helgrind_summary.log; \
	COUNT=0; \
	for args in $(ARGS_LIST); do \
		COUNT=$$((COUNT+1)); \
		$(call run_helgrind_test, $$args); \
	done

tests_all: tests tests_valgrind tests_helgrind

.PHONY: all clean fclean re debug sanitize unit_tests tests helgrind_tests
