/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:49:02 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/04 17:02:57 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "philo.h"

int contains_only_digits(char *str);
int is_valid_single_argument(char *str);
int is_valid_input(char **argv);
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
    check_test("contains_only_digits(\"1\")", 1, contains_only_digits("1"));
    check_test("contains_only_digits(\"123\")", 1, contains_only_digits("123"));
    check_test("contains_only_digits(\"0\")", 1, contains_only_digits("0"));
    check_test("contains_only_digits(\"0_\")", 0, contains_only_digits("0_"));
    check_test("contains_only_digits(\"-1\")", 0, contains_only_digits("-1"));
    check_test("contains_only_digits(\"2a\")", 0, contains_only_digits("2a"));
    check_test("contains_only_digits(\"a\")", 0, contains_only_digits("a"));
    check_test("contains_only_digits(\"-a\")", 0, contains_only_digits("-a"));
}

int main(void)
{
    test_contains_only_digits();
}
