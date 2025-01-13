/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 00:17:25 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/13 22:24:48 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/**
 * Initializes philosophers.
 */
int init_philos(t_data *data)
{
	int	i;
	data->philos = malloc(data->no_of_philosophers * sizeof(t_philosopher));
	if (data->philos == NULL)
		return (MALLOC_FAIL);
	
	i = 0;
	while (i < data->no_of_philosophers)
	{
		data->philos[i].id = i + 1;
		data->philos[i].is_alive = 1;
		data->philos[i].last_meal_time_ms = get_runtime(data);
		data->philos[i].meals_count = 0;
		data->philos[i].fork_left = &data->forks[i];
		data->philos[i].fork_right = &data->forks[(i + 1) % data->no_of_philosophers];
		if (EXTENDED_OUTPUT)
			printf(GREEN "Philosopher %d initialized.\n" RESET, data->philos[i].id);
		data->philos[i].data = data;
		i++;
	}
	data->philo_threads = malloc(data->no_of_philosophers * sizeof(pthread_t));
	
	return (EXIT_SUCCESS);
}
