/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 01:18:05 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/04 15:41:30 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// number_of_philosophers: The number of philosophers and also the number
// of forks.

// time_to_die (inmilliseconds): Ifaphilosopherdidn’tstarteatingtime_to_die
// milliseconds since the beginning of their last meal or the beginning of the sim-
// ulation, they die.

// time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
// During that time, they will need to hold two forks.

// time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.

// number_of_times_each_philosopher_must_eat (optional argument)

int main(int argc, char **argv)
{
    if (argc - 1 < 4 || argc - 1 > 5)
    {
        printf("Please provide 4-5 arguments.\n");
        return (EXIT_FAILURE);
    }
    argv++;
    if (is_valid_input(argv) == 0)
    {
        printf("Your input contains non-digit characters.\n");
        return (EXIT_FAILURE);
    }
    printf("Arguments: all checks passed.\n");
    return (EXIT_SUCCESS);
}
