/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:49:02 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/08 16:55:53 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int contains_only_digits(const char *str)
{
	if (ft_strlen(str) == 0)
		return (FALSE);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

int is_valid_single_argument(const char *str)
{
	int is_valid_single_argument;

	is_valid_single_argument = TRUE;
	if (!contains_only_digits(str))
		is_valid_single_argument = FALSE;
	return (is_valid_single_argument);
}

int is_valid_input(char **argv, int argc)
{
	int	i;

	if (argc - 1 < 4 || argc - 1 > 5)
    {
        printf(MSG_WRONG_ARGUMENT_COUNT);
        return (FALSE);
    }
	i = 1;
	if (int_atoi(argv[i++]) > MAX_PHILOS)
    {
        printf(MSG_TOO_MANY_PHILOS);
        return (FALSE);
    }
	while (argv[i])
	{
		if (is_valid_single_argument(argv[i]) == FALSE)
		{
			printf("One or more arguments are wrong.\n");
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
