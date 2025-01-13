/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:32:44 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/13 22:13:08 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * get current time value in seconds (epoch seconds)
 */
long	get_current_time_s(void)
{
	struct timeval time_value;

	gettimeofday(&time_value, NULL);
	return (time_value.tv_sec);
}

/**
 * get the microseconds part of current epoch time
 */
long	get_current_time_us(void)
{
	struct timeval time_value;

	gettimeofday(&time_value, NULL);
	return (time_value.tv_usec);
}
/**
 * get current time in ms
 */
long long get_current_time()
{
	return (get_current_time_s() * 1e3 + get_current_time_us() / 1e3);
}

long long get_runtime(t_data *data)
{
	return (get_current_time() - data->simulation_start_time);
}