# Regular Colors
BLACK  = \033[0;30m
RED    = \033[0;31m
GREEN  = \033[0;32m
YELLOW = \033[0;33m
BLUE   = \033[0;34m
MAGENTA = \033[0;35m
CYAN   = \033[0;36m
WHITE  = \033[0;37m

# Bold Colors
B_BLACK  = \033[1;30m
B_RED    = \033[1;31m
B_GREEN  = \033[1;32m
B_YELLOW = \033[1;33m
B_BLUE   = \033[1;34m
B_MAGENTA = \033[1;35m
B_CYAN   = \033[1;36m
B_WHITE  = \033[1;37m

# Underline Colors
U_BLACK  = \033[4;30m
U_RED    = \033[4;31m
U_GREEN  = \033[4;32m
U_YELLOW = \033[4;33m
U_BLUE   = \033[4;34m
U_MAGENTA = \033[4;35m
U_CYAN   = \033[4;36m
U_WHITE  = \033[4;37m

# Background Colors
BG_BLACK  = \033[40m
BG_RED    = \033[41m
BG_GREEN  = \033[42m
BG_YELLOW = \033[43m
BG_BLUE   = \033[44m
BG_MAGENTA = \033[45m
BG_CYAN   = \033[46m
BG_WHITE  = \033[47m

# Reset
RST = \033[0m

# Reset
HEADER_FILE = header.generated

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

$(NAME): $(HEADER_FILE) $(OBJ)
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
	rm ./unit_tests

# Helgrind launch
HELGRIND = valgrind --tool=helgrind

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


helgrind_tests: re
	mkdir -p logs
	@echo "Running Helgrind Tests..." > logs/helgrind_summary.log; \
	COUNT=0; \
	for args in $(ARGS_LIST); do \
		COUNT=$$((COUNT+1)); \
		$(call run_helgrind_test, $$args); \
	done


.PHONY: all clean fclean re debug sanitize unit_tests tests helgrind_tests header

INFO1 = $(CYAN)42 Berlin Core Curriculum – dmlasko$(RST)
INFO2 = $(MAGENTA)Mandatory part – Evaluation \#1$(RST)

# Header will be generated ONLY when $(NAME) needs to be rebuilt
$(HEADER_FILE): $(OBJ)
	@touch $(HEADER_FILE)
	@echo
	@echo " _____                                                             _____ "
	@echo "( ___ )           $(INFO1)             ( ___ )"
	@echo " |   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|   | "
	@echo " |   |  ____  _     _ _                       _                    |   | "
	@echo " |   | |  _ \| |__ (_) | ___  ___  ___  _ __ | |__   ___ _ __ ___  |   | "
	@echo " |   | | |_) | '_ \| | |/ _ \/ __|/ _ \| '_ \| '_ \ / _ \ '__/ __| |   | "
	@echo " |   | |  __/| | | | | | (_) \__ \ (_) | |_) | | | |  __/ |  \__ \ |   | "
	@echo " |   | |_|   |_| |_|_|_|\___/|___/\___/| .__/|_| |_|\___|_|  |___/ |   | "
	@echo " |   |                                 |_|                         |   | "
	@echo " |___|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|___| "
	@echo "(_____)              $(INFO2)               (_____)"