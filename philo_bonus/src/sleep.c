/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:21:32 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/31 18:07:24 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long	get_remaining_time(long long sleep_time_ms, \
										long long sleep_start_time_ms)
{
	return (sleep_time_ms - (get_epoch_time_ms() - sleep_start_time_ms));
}

void	msleep(t_data *data, unsigned int sleep_time_ms)
{
	long long	sleep_start_time_ms;
	long long	remaining_time;

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
	}
}
