/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:46:02 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/03 20:11:35 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * Wrapper for pthread_join() function.
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
 * Wrapper for pthread_create() function.
 */
int	create_philo_threads(t_data *data)
{
	int	i;
	int	pid;

	i = 0;
	//data->philo_threads = malloc(sizeof(pthread_t) * data->no_of_philos);
	//if (!data->philo_threads)
	//	return (MALLOC_FAIL);
	while (i < data->no_of_philos)
	{
		pid = fork();
		if (DEBUG && pid == 0)
			printf("Philo process [%d] created!\n", data->philos[i].id);
		if (pid == 0)
			philosopher_routine(data);
		i++;
	}
	return (EXIT_SUCCESS);
}
