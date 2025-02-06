/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 01:18:05 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/06 17:39:56 by dmlasko          ###   ########.fr       */
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
	if (data.sem_forks == SEM_FAILED)
	{
		perror("sem_open failed");
		return (EXIT_FAILURE);
	}
	printf(B_MAGENTA ">>>>>>>>>>>>>>>>>>> Created a semaphore with value of: %d\n" RST, data.no_of_philos);
	data.sem_print = sem_open("/print", O_CREAT, 0666, 1);
	puts("Semaphores created");
	if (init_philos(&data))
		return (EXIT_FAILURE);
	puts("All philos initialized");
	create_philo_processes(&data);
	wait_for_all_philos(&data);
	puts("Freeing data...");
	free_data(&data);

	return (EXIT_SUCCESS);
}
