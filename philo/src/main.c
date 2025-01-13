/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 01:18:05 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/13 01:31:19 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// philosophers_len: The number of philosophers and also the number
// of forks.

// time_to_die_ms (inmilliseconds): Ifaphilosopherdidn’tstarteatingtime_to_die_ms
// milliseconds since the beginning of their last meal or the beginning of the sim-
// ulation, they die.

// time_to_eat_ms (in milliseconds): The time it takes for a philosopher to eat.
// During that time, they will need to hold two forks.

// time_to_sleep_ms (in milliseconds): The time a philosopher will spend sleeping.

// no_of_meals_required (optional argument)

int main(int argc, char **argv)
{
    t_data data;
    
    if (is_valid_input(argv, argc) == FALSE)
        return (EXIT_FAILURE);
    printf("Arguments: all checks passed, continuing work...\n");
    init_data(&data, argc, argv);
    if (data.no_of_meals_required == 0)
        return (-1);
    init_forks(&data);
    init_philos(&data);
    start_philo_threads(&data);
    start_monitor(&data);
    join_philo_threads(&data);
    join_monitor_thread(&data);
    destroy_forks(&data);
    if (EXTENDED_OUTPUT)
        printf(YELLOW "TOTAL RUN TIME: %lld\n" RESET, get_runtime_ms(&data));
    return (EXIT_SUCCESS);
}
