/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:45:51 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/22 12:37:24 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_meal_count(t_data *data)
{
    int i;
    t_philosopher *philo;

    philo = data->philos;
    i = 0;
    while (i < data->no_of_philosophers)
    {
        printf(B_MAGENTA"Philosopher [%d]: %d\n"RESET, philo[i].id, philo[i].meals_count);
        i++;
    }
}

void print_total_runtime(t_data *data)
{
    printf(YELLOW "TOTAL RUN TIME: %lld ms.\n" RESET, get_simulation_runtime_ms(data));
}

void print_stats(t_data *data)
{
    print_meal_count(data);
    print_total_runtime(data);
}