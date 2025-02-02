/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 01:18:05 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/01 19:44:37 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (is_valid_input(argv, argc) == FALSE)
		return (INVALID_INPUT);
	if (init_data(&data, argc, argv))
		return (EXIT_FAILURE);
	if (data.no_of_meals_required == 0)
		return (MEALS_REQUIRED_ZERO);
	if (init_forks(&data) || init_philos(&data))
		return (EXIT_FAILURE);
	create_philo_threads(&data);
	create_monitor(&data);
	if (DEBUG)
		printf(YELLOW"START TIMESTAMP: %ld ms.\n"RST, get_sim_runtime_ms(&data));
	join_philo_threads(&data);
	join_monitor_thread(&data);
	if (DEBUG)
		print_stats(&data);
	free_data(&data);
	return (EXIT_SUCCESS);
}
