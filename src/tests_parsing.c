/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:49:02 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/04 21:41:41 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "philo.h"

int contains_only_digits(char *str);
int is_valid_single_argument(char *str);
int is_valid_input(char **argv, int argc);
int int_atoi(char *str);

void check_test(const char *test_name, int expected, int actual)
{
	if (expected != actual)
		printf("%sTest failed: %s (expected %d, got %d)\n%s", RED, test_name, expected, actual, RESET);
	else
		printf("%sTest passed: %s (expected %d, got %d)\n%s", GREEN, test_name, expected, actual, RESET);

}

void test_contains_only_digits(void)
{
	printf("\n%s%s%s\n", YELLOW, "contains_only_digits", RESET);
	printf("--------------------------------------------------------\n");
	check_test("contains_only_digits(\"1\")", 1, contains_only_digits("1"));
	check_test("contains_only_digits(\"123\")", 1, contains_only_digits("123"));
	check_test("contains_only_digits(\"0\")", 1, contains_only_digits("0"));
	check_test("contains_only_digits(\"0 0\")", 0, contains_only_digits("0 0"));
	check_test("contains_only_digits(\"\")", 0, contains_only_digits(""));
	check_test("contains_only_digits(\"0_\")", 0, contains_only_digits("0_"));
	check_test("contains_only_digits(\"-1\")", 0, contains_only_digits("-1"));
	check_test("contains_only_digits(\"2a\")", 0, contains_only_digits("2a"));
	check_test("contains_only_digits(\"a\")", 0, contains_only_digits("a"));
	check_test("contains_only_digits(\"-a\")", 0, contains_only_digits("-a"));
}

void test_is_valid_single_argument(void)
{
	printf("\n%s%s%s\n", YELLOW, "is_valid_single_argument", RESET);
	printf("--------------------------------------------------------\n");
	check_test("is_valid_single_argument(\"1\")", 1, is_valid_single_argument("1"));
	check_test("is_valid_single_argument(\"123\")", 1, is_valid_single_argument("123"));
	check_test("is_valid_single_argument(\"0\")", 1, is_valid_single_argument("0"));
	check_test("is_valid_single_argument(\"0 0\")", 0, is_valid_single_argument("0 0"));
	check_test("is_valid_single_argument(\"\")", 0, is_valid_single_argument(""));
	check_test("is_valid_single_argument(\"0_\")", 0, is_valid_single_argument("0_"));
	check_test("is_valid_single_argument(\"-1\")", 0, is_valid_single_argument("-1"));
	check_test("is_valid_single_argument(\"2a\")", 0, is_valid_single_argument("2a"));
	check_test("is_valid_single_argument(\"a\")", 0, is_valid_single_argument("a"));
	check_test("is_valid_single_argument(\"-a\")", 0, is_valid_single_argument("-a"));
}

void test_is_valid_input(void)
{
	int	i;
	printf("\n%s%s%s\n", YELLOW, "is_valid_input", RESET);
	printf("--------------------------------------------------------\n");
	i = 1;
	check_test("test 1", 1, is_valid_input((const char *[]){"1", "2", "3", "4", '\0'}, 4));
	check_test("test 2", 1, is_valid_input((const char *[]){"1", "2", "3", "4", "5", '\0'}, 5));
	check_test("test 3", 0, is_valid_input((const char *[]){"1", "2a", "3", "4", '\0'}, 4));
	check_test("test 4", 0, is_valid_input((const char *[]){"1", "2", "-3", "4", "5", '\0'}, 5));
	check_test("test 5", 0, is_valid_input((const char *[]){"1", "2", "3", "4", "5", "6", '\0'}, 6));
	check_test("test 6", 0, is_valid_input((const char *[]){"1", "2", '\0'}, 2));
	check_test("test 7", 0, is_valid_input((const char *[]){"1", "2", "3", '\0'}, 3));

}

int main(void)
{
	test_contains_only_digits();
	test_is_valid_single_argument();
	test_is_valid_input();
}
