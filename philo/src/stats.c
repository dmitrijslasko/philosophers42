/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:45:51 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/20 11:45:57 by dmlasko          ###   ########.fr       */
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
