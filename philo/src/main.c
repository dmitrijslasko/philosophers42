/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 01:18:05 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/11 14:01:29 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// philosophers_len: The number of philosophers and also the number
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
    t_data data;
    
    if (is_valid_input(argv, argc) == FALSE)
        return (EXIT_FAILURE);
    printf("Arguments: all checks passed, continuing work...\n");
    init_data(&data, argc, argv);
    if (data.number_of_times_each_philosopher_must_eat == 0)
        return (-1);
    init_forks(&data);
    init_philos(&data);
    start_threads(&data);
    join_threads(&data);
    destroy_forks(&data);
    printf(YELLOW "MS RUN TIME: %lld\n" RESET, get_runtime(&data));
    return (EXIT_SUCCESS);
}
