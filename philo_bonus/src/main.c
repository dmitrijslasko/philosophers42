/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 01:18:05 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/08 01:12:39 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;
	// pid_t	parent_pid;

	if (is_valid_input(argv, argc) == FALSE)
		return (INVALID_INPUT);
	puts("Input is valid");
	//data = safe_malloc(sizeof(t_data));
	if (init_data(&data, argc, argv))
		return (EXIT_FAILURE);
	puts("Data is initialized");
	if (data.no_of_meals_required == 0)
		return (MEALS_REQUIRED_ZERO);
	puts("Number of meals non-zero");
	sem_unlink("/forks");
	sem_unlink("/print");
	data.sem_forks = sem_open("/forks", O_CREAT, 0666, data.no_of_philos);
	//if (&data->sem_forks == SEM_FAILED)
	//{
	//	perror("sem_open failed");
	//	return (EXIT_FAILURE);
	//}
	printf(B_MAGENTA ">>>>>>>>>>>>>>>>>>> Created a semaphore with value of: %d\n" RST, data.no_of_philos);
	data.sem_print = sem_open("/print", O_CREAT, 0666, 1);
	puts("Semaphores created");
	// parent_pid = getpid();
	if (init_philos(&data))
		return (EXIT_FAILURE);
	printf("All philos initialized\n");
	create_philo_processes(&data);
	int i = 0;
	while (i < data.no_of_philos)
	{
		waitpid(data.process_pids[i], NULL, 0);
		i++;
	}
	// puts("Let's free it!");
	free_data(&data);
	// puts("All freed!");
	return (EXIT_SUCCESS);
}
