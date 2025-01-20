/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:32:44 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/20 12:19:12 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * get current time value in seconds (epoch seconds)
 */
long	get_epoch_time_s(void)
{
	struct timeval time_value;

	gettimeofday(&time_value, NULL);
	return (time_value.tv_sec);
}

/**
 * get the microseconds part of current epoch time
 */
long	get_epoch_time_us(void)
{
	struct timeval time_value;

	gettimeofday(&time_value, NULL);
	return (time_value.tv_usec);
}
/**
 * get current time in ms
 */
long long get_epoch_time()
{
	return (get_epoch_time_s() * (1e3) + get_epoch_time_us() / (1e3));
}

long long get_simulation_runtime_ms(t_data *data)
{
	long long runtime_ms;

	runtime_ms = 0;
	mutex_operation(&data->data_access_mutex, LOCK);
	runtime_ms = get_epoch_time() - data->simulation_start_time;
	mutex_operation(&data->data_access_mutex, UNLOCK);
	return (runtime_ms);
}
