/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:21:32 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/24 00:18:44 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void msleep(t_data *data, unsigned int sleep_time_ms) 
{
	// int	can_continue;
	(void)data;
	long long sleep_start_time_ms = get_epoch_time_ms();
	long long remaining_time;

	// can_continue = 0;
	while ((remaining_time = sleep_time_ms - (get_epoch_time_ms() - sleep_start_time_ms)) > 0) 
	{	
		// mutex_operation(&data->data_access_mutex, LOCK);
		// if (data->simulation_is_on == 0)
		// 	can_continue = 1;
		// mutex_operation(&data->data_access_mutex, UNLOCK);
		// if (can_continue)
		// 	break;
		if (remaining_time > 10)
			usleep(1000);
		else
			usleep(20);
	}
}
