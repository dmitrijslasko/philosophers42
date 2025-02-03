/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 01:18:05 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/03 20:07:59 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;
	sem_t	*forks;

	if (is_valid_input(argv, argc) == FALSE)
		return (INVALID_INPUT);
	if (init_data(&data, argc, argv))
		return (EXIT_FAILURE);
	if (data.no_of_meals_required == 0)
		return (MEALS_REQUIRED_ZERO);

	if (init_philos(&data))
		return (EXIT_FAILURE);
	forks = sem_open("forks", O_CREAT, 0666, data.no_of_philos);
	if (forks == SEM_FAILED)
	{
		perror("sem_open failed");
		return (EXIT_FAILURE);
	}
	printf("Created a semaphore with value of: %d\n", data.no_of_philos);
	create_philo_threads(&data);
	create_monitor(&data);
	if (DEBUG)
		printf(YELLOW"START TIME: %ld ms.\n"RST, get_sim_runtime_ms(&data));
	join_philo_threads(&data);
	join_monitor_thread(&data);
	if (DEBUG)
		print_stats(&data);
	free_data(&data);
	sem_unlink("forks");
	return (EXIT_SUCCESS);
}
