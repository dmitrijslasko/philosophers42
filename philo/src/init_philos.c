/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 00:17:25 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/01 17:01:24 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_philo_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_of_philos)
	{
		mutex_operation(&data->philos[i].philo_data_access_mutex, DESTROY);
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * Initializes philosophers.
 */
int	init_philos(t_data *data)
{
	int	i;

	data->philos = safe_malloc(data->no_of_philos * sizeof(t_philosopher));
	if (data->philos == NULL)
		return (MALLOC_FAIL);
	i = 0;
	while (i < data->no_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal_time_ms = 0;
		data->philos[i].meals_count = 0;
		data->philos[i].fork_left = &data->forks[i];
		data->philos[i].fork_right = &data->forks[(i + 1) % data->no_of_philos];
		if (DEBUG)
			printf(GREEN "Philo [%d] initialized.\n" RST, data->philos[i].id);
		data->philos[i].data = data;
		mutex_operation(&data->philos[i].philo_data_access_mutex, INIT);
		i++;
	}
	return (EXIT_SUCCESS);
}
