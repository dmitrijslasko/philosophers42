/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:46:02 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/04 21:42:43 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * Wrapper for pthread_join() function.
 */
int	join_philo_threads(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->no_of_philos)
	{
		waitpid(data->process_pids[i], &status, 0);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	kill_all(t_data *data)
{
	int	i;

	while (i < data->no_of_philos)
	{
		kill(data->process_pids[i], 9);
		printf("[%d] killed!\n", data->process_pids[i]);
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
	while (i < data->no_of_philos)
	{
		pid = fork();
		if (pid == 0)
		{
			data->philos->id = i + 1;
			philosopher_routine(data);
		}
		else
			data->process_pids[i] = pid;
		i++;
	}
	return (EXIT_SUCCESS);
}
