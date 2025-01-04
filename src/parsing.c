/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:49:02 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/04 21:21:52 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "assert.h"

int	ft_strlen(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int contains_only_digits(char *str)
{
	if (ft_strlen(str) == 0)
		return (0);
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

int is_valid_input(char **argv, int argc)
{
	int	i;

	if (argc < 4 || argc > 5)
    {
        printf("Please provide 4-5 arguments.\n");
        return (0);
    }
	i = 0;
	if (int_atoi(argv[i++]) > MAX_PHILOS)
    {
        printf("Too many philosophers, let's keep the count under 200.\n");
        return (0);
    }
	while (argv[i])
	{
		if (is_valid_single_argument(argv[i]) == 0)
			return (0);
		i++;
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
