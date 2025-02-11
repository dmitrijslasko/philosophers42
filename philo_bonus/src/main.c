/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 01:18:05 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/11 12:01:43 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;
	// int		parent_pid;
	int	i;

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
	if (data.is_philo == 1)
	{
		if (DEBUG)
			print_stats(&data);
		free_philo_data(&data);
		return (EXIT_SUCCESS);
	}
	i = 0;
	if (data.is_philo == 0)
	{
		while (i < data.no_of_philos)
			waitpid(data.process_pids[i++], NULL, 0);
		free_data(&data);
	}
	return (EXIT_SUCCESS);
}
