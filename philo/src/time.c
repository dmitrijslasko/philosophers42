/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:32:44 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/13 00:56:18 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * get the seconds part of current epoch time
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
long long get_current_time_ms()
{
	return (get_epoch_time_s() * 1000 + get_epoch_time_us() / 1000);
}

long long get_runtime_ms(t_data *data)
{
	return (get_current_time_ms() - data->start_time_ms);
}