/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 01:18:05 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/17 00:51:41 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// no_of_philosophers: The number of philosophers and also the number
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
        return (INVALID_INPUT);
    if (init_data(&data, argc, argv))
        return (EXIT_FAILURE);
    if (data.no_of_meals_required == 0)
        return (MEALS_REQUIRED_ZERO);
    if (init_forks(&data))
        return (EXIT_FAILURE);
    if (init_philos(&data))
        return (EXIT_FAILURE);

    create_philo_threads(&data);
    create_monitor(&data);
    
    join_philo_threads(&data);
    join_monitor_thread(&data);

    destroy_forks(&data);
    mutex_operation(&data.data_access_mutex, DESTROY);
    mutex_operation(&data.status_write_mutex, DESTROY);
    if (DEBUG)
        printf(YELLOW "TOTAL RUN TIME: %lld ms.\n" RESET, get_runtime(&data));
    return (EXIT_SUCCESS);
}
