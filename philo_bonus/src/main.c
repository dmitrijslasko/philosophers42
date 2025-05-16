/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 01:18:05 by dmlasko           #+#    #+#             */
/*   Updated: 2025/05/16 12:36:45 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int cleanup_child_processes(t_data *data)
{
	if (data->is_philo == 1)
	{
		if (DEBUG)
			print_stats(data);
		free_philo_data(data);
	}
	return (EXIT_SUCCESS);
}

int cleanup_parent_process(t_data *data)
{
	int	i;

	if (data->is_philo == 0)
	{
		i = 0;
		while (i < data->no_of_philos)
			waitpid(data->process_pids[i++], NULL, 0);
		free_data(data);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief This version of philosophers works with processes and semaphores.
 * (Instead of threads and forks in the mandatory part).
 * The flow of the program is this:
 * 1) Check input for validity
 * 2) Initialize [table] data
 * 3) Unlink (delete) semaphores that might still be there from previous runs
 * 4) Open new semaphores for the forks and the print output
 * 5) Initialize philos
 * 6) Create philo processes (and make them run the programmed routine)
 * 7) Parent process wait for philos to start
 * 8) Free philos' process memory
 * 9) Free parent process memory
 *
 * Two main functions that control semaphores are sem_post (release) and
 * sem_wait (take / wait for access).
 * @param argc
 * @param argv
 * @return int
 */
int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (is_valid_input(argv, argc) == FALSE)
		return (INVALID_INPUT);
	if (init_data(&data, argc, argv))
		return (EXIT_FAILURE);
	if (data.no_of_meals_required == 0)
		return (MEALS_REQUIRED_ZERO);
	sem_unlink("/forks");
	sem_unlink("/print");
	data.sem_forks = sem_open("/forks", O_CREAT, 0666, data.no_of_philos);
	data.sem_print = sem_open("/print", O_CREAT, 0666, 1);
	if (init_philos(&data))
		return (EXIT_FAILURE);
	create_philo_processes(&data);
	if (data.is_philo == 0)
	{
		i = 0;
		while (i < data.no_of_philos)
			waitpid(data.process_pids[i++], NULL, 0);
	}
	cleanup_child_processes(&data);
	cleanup_parent_process(&data);
	return (EXIT_SUCCESS);
}
