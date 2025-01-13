/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:49:02 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/13 22:19:37 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline int is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int contains_only_digits(const char *str)
{
	if (ft_strlen(str) == 0)
		return (FALSE);
	while (*str)
	{
		if (!is_digit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

int is_valid_single_argument(const char *str)
{
	if (ft_strlen(str) > MAX_ARGUMENT_LEN)
		return (FALSE);
	if (!contains_only_digits(str))
		return (FALSE);
	return (TRUE);
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
	if (int_atoi(argv[i]) > MAX_PHILOS)
    {
        printf(MSG_TOO_MANY_PHILOS);
        return (FALSE);
    }
	else if (int_atoi(argv[i]) == 0)
    {
        printf(MSG_ZERO_PHILOS);
        return (FALSE);
    }
	i++;
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
