/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 00:17:25 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/17 00:25:42 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	int	i;
	
	data->forks = safe_malloc(data->no_of_philosophers * sizeof(t_fork));
	if (!data->forks)
		return (MALLOC_FAIL);
	i = 0;
	while (i < data->no_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i].fork_mutex, NULL);
		data->forks[i].fork_taken = 0;
		if (DEBUG)
			printf(YELLOW"Fork %d initialized\n"RESET, i + 1);
		i++;
	}
	return (EXIT_SUCCESS);
}

int free_forks(t_data *data)
{
	int i;

	i = 0;
	mutex_operation(&data->data_access_mutex, LOCK);
	while (i < data->no_of_philosophers)
	{
		if (data->forks[i].fork_taken)
		{
			pthread_mutex_unlock(&data->forks[i].fork_mutex);
			printf(YELLOW"Fork %d unlocked\n"RESET, i + 1);
		}
		i++;
		
	}
	mutex_operation(&data->data_access_mutex, UNLOCK);
	return (EXIT_SUCCESS);
}

int	destroy_forks(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->no_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i].fork_mutex);
		if (DEBUG)
			printf(YELLOW"Fork [%d] destroyed\n"RESET, i + 1);
		i++;
	}
	return (EXIT_SUCCESS);
}
