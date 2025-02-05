/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 01:18:05 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/05 19:53:45 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philosopher philo;

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
	philo.id = 0;
	philo.is_alive = 1;
	philo.is_full = 0;
	philo.last_meal_time_ms = get_epoch_time_ms();
	data.philos = philo;
	if (init_philos(&data))
		return (EXIT_FAILURE);
	puts("All philos initialized");
	create_philo_threads(&data);
	join_philo_threads(&data);
	puts("Freeing data...");
	free_data(&data);

	return (EXIT_SUCCESS);
}
