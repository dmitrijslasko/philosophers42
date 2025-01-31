/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:57:42 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/31 18:10:02 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * A monitor thread routine.
 */
void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = arg;
	wait_for_all_threads(data);
	while (all_philos_are_alive(data)
		&& (!all_philos_are_full(data) || data->no_of_meals_required == -1))
		usleep(MONITOR_FREQ_US);
	return (NULL);
}

/**
 * Wrapper for pthread_create() function.
 */
int	create_monitor(t_data *data)
{
	pthread_create(&data->monitor_thread, NULL, monitor_routine, (void *)data);
	if (DEBUG)
		printf(B_MAGENTA">>>>>>>>>>>>>> MONITOR THREAD CREATED\n"RST);
	set_protected_value(data, &data->simulation_status, 1);
	return (EXIT_SUCCESS);
}

void	join_monitor_thread(t_data *data)
{
	pthread_join(data->monitor_thread, NULL);
}
