/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:21:32 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/02 22:31:35 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	get_remaining_time(long sleep_time_ms, \
										long sleep_start_time_ms)
{
	return (sleep_time_ms - (get_epoch_time_ms() - sleep_start_time_ms));
}

void	msleep(t_data *data, unsigned int sleep_time_ms)
{
	long	sleep_start_time_ms;
	long	remaining_time;

	(void)data;
	sleep_start_time_ms = get_epoch_time_ms();
	remaining_time = get_remaining_time(sleep_time_ms, sleep_start_time_ms);
	while (remaining_time > 0)
	{
		if (remaining_time > 10)
			usleep(1000);
		else
			usleep(10);
		remaining_time = get_remaining_time(sleep_time_ms, sleep_start_time_ms);
		mutex_operation(data->data_access_mutex, LOCK);
		if (data->simulation_status == 0)
		{
			mutex_operation(data->data_access_mutex, UNLOCK);
			break ;
		}
		mutex_operation(data->data_access_mutex, UNLOCK);
	}
}
