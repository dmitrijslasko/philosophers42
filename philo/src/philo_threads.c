/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:46:02 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/01 16:36:52 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Wrapper for pthread_join() function - specifically for philo threads.
 */
int	join_philo_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_of_philos)
	{
		pthread_join(data->philo_threads[i], NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * Wrapper for pthread_create() function - specifically for philo threads.
 */
int	create_philo_threads(t_data *data)
{
	int	i;

	i = 0;
	data->philo_threads = malloc(sizeof(pthread_t) * data->no_of_philos);
	if (!data->philo_threads)
		return (MALLOC_FAIL);
	while (i < data->no_of_philos)
	{
		pthread_create(&data->philo_threads[i], \
			NULL, philosopher_routine, (void *)&data->philos[i]);
		if (DEBUG)
			printf("Philo thread [%d] created!\n", data->philos[i].id);
		i++;
	}
	return (EXIT_SUCCESS);
}
