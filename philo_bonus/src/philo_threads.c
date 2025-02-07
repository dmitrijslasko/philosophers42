/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:46:02 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/07 02:23:41 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	wait_for_all_philos(t_data *data)
{
	int	status;
	int i;

	i = 0;
	while (i < data->no_of_philos)
	{
		waitpid(data->process_pids[i], &status, 0);
		i++;
	}

	return (EXIT_SUCCESS);
}


int	kill_all_philos(t_data *data)
{
	int	i;

	i = 0;
	waitpid(-1, NULL, 0);
	while (i < data->no_of_philos)
	{
		kill(data->process_pids[i], SIGTERM);
		// printf("[%d] killed!\n", data->process_pids[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * Forking all day long.
 */
int	create_philo_processes(t_data *data)
{
	int	i;
	int	pid;

	pid = 0;
	i = 0;
	data->process_pids = safe_malloc(sizeof(int) * data->no_of_philos);
	while (i < data->no_of_philos)
	{
		pid = fork();
		if (pid == 0)		// child process
		{
			data->philo_index = i;
			create_monitor(data);
			pthread_detach(data->monitor_thread);
 			philosopher_routine(data);
			exit (0);
		}
		else				// main process
			data->process_pids[i] = pid;
		i++;
	}
	return (EXIT_SUCCESS);
}
