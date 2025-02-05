/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:46:02 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/05 17:39:51 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


/**
 * Wrapper for pthread_join() function.
 */
int	join_philo_threads(t_data *data)
{
	int	status;

	waitpid(-1, &status, 0);
	kill_all(data);

	return (EXIT_SUCCESS);
}

int	kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_of_philos)
	{
		kill(data->process_pids[i], SIGTERM);
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
	data->process_pids = safe_malloc(sizeof(int) * data->no_of_philos);
	while (i < data->no_of_philos)
	{
		pid = fork();
		if (pid == 0)		// child process
		{
			philosopher_routine(data, i);
		}
		else				// main process
			data->process_pids[i] = pid;
		i++;
	}
	return (EXIT_SUCCESS);
}
