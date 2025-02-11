/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:57:42 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/11 11:39:32 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * A monitor thread routine.
 */
//void	*monitor_routine(void *arg)
//{
//	t_data	*data;

//	data = arg;
//	//wait_for_all_threads(data);
//	//while (all_philos_are_alive(data) && (all_philos_are_full(data) == 0))
//	//	usleep(MONITOR_FREQ_US);
//	//exit(EXIT_SUCCESS);
//	return (NULL);
//}

/**
 * Wrapper for pthread_create() function - specifically for the monitor thread.
 */
int	create_monitor(t_data *data)
{
	if (DEBUG)
		printf(B_MAGENTA">>>>>>>>>>>>>> MONITOR THREAD CREATED [%d]\n"RST, data->philo_index);
	pthread_create(&data->monitor_thread, NULL, monitor_philo_status, (void *)data);
	return (EXIT_SUCCESS);
}

/**
 * Wrapper for pthread_join() function - specifically for the monitor thread.
 */
void	join_monitor_thread(t_data *data)
{
	pthread_join(data->monitor_thread, NULL);
}
