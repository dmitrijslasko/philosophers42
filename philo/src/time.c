/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:32:44 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/31 18:13:31 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * get current time value in seconds (epoch seconds)
 */
long	get_epoch_time_s_part(void)
{
	struct timeval	time_value;

	gettimeofday(&time_value, NULL);
	return (time_value.tv_sec);
}

/**
 * get the microseconds part of current epoch time
 */
long	get_epoch_time_us_part(void)
{
	struct timeval	time_value;

	gettimeofday(&time_value, NULL);
	return (time_value.tv_usec);
}

long long	get_epoch_time_us(void)
{
	return (get_epoch_time_s_part() * 1e6 + get_epoch_time_us_part());
}

/**
 * get current time in ms
 */
long long	get_epoch_time_ms(void)
{
	return (get_epoch_time_s_part() * 1e3 + get_epoch_time_us_part() / 1e3);
}

long long	get_sim_runtime_ms(t_data *data)
{
	long long	runtime_ms;

	runtime_ms = get_epoch_time_ms() - data->simulation_start_time_ms;
	return (runtime_ms);
}
