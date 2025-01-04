/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:49:02 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/04 16:37:59 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "assert.h"

int contains_only_digits(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int is_valid_single_argument(char *str)
{
	int is_valid_single_argument;

	is_valid_single_argument = 1;
	if (!contains_only_digits(str))
		is_valid_single_argument = 0;
	return (is_valid_single_argument);
}

int is_valid_input(char **argv)
{
	while (*argv)
	{
		printf("CHECKING ARGUMENT: %s\n", *argv);
		if (is_valid_single_argument(*argv) == 0)
			return (0);
		argv++;
	}
	return (1);
}

int int_atoi(char *str)
{
	unsigned int    nb;

	nb = 0;
	while (*str)
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	return (nb);
}
