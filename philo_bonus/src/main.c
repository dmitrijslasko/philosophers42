/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 01:18:05 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/04 21:34:17 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (is_valid_input(argv, argc) == FALSE)
		return (INVALID_INPUT);
	puts("Input is valid");
	if (init_data(&data, argc, argv))
		return (EXIT_FAILURE);
	puts("Data is initialized");
	if (data.no_of_meals_required == 0)
		return (MEALS_REQUIRED_ZERO);
	puts("Number of meals non-zero");
	sem_unlink("/forks");
	sem_unlink("/print");
	data.sem_forks = sem_open("/forks", O_CREAT, 0666, data.no_of_philos);
	data.sem_print = sem_open("/print", O_CREAT, 0666, 1);
	if (init_philos(&data))
		return (EXIT_FAILURE);
	puts("Philos initialized");
	printf("TIME TO EAT: %d\n", data.time_to_eat_ms);
	printf("TIME TO SLEEP: %d\n", data.time_to_sleep_ms);
	if (data.sem_forks == SEM_FAILED)
	{
		perror("sem_open failed");
		return (EXIT_FAILURE);
	}
	printf("Created a semaphore with value of: %d\n", data.no_of_philos);
	create_philo_threads(&data);
	if (DEBUG)
		printf(YELLOW"START TIME: %ld ms.\n"RST, get_sim_runtime_ms(&data));
	join_philo_threads(&data);
	if (DEBUG)
		print_stats(&data);
	free_data(&data);
	//sem_unlink("/forks");
	//sem_unlink("/print");
	return (EXIT_SUCCESS);
}
