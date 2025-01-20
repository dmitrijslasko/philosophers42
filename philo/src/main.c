/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 01:18:05 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/20 13:34:46 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
    {
        printf(YELLOW "TOTAL RUN TIME: %lld ms.\n" RESET, get_simulation_runtime_ms_ms(&data));
        print_meal_count(&data);
    }
    return (EXIT_SUCCESS);
}
