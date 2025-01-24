/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:21:32 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/24 02:26:05 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msleep(t_data *data, unsigned int sleep_time_ms)
{
	long long	sleep_start_time_ms;
	long long	remaining_time_ms;

	(void)data;
	sleep_start_time_ms = get_epoch_time_ms();
	remaining_time_ms = sleep_time_ms - (get_epoch_time_ms() - sleep_start_time_ms);
	while (remaining_time_ms > 0)
	{
		remaining_time_ms = sleep_time_ms - (get_epoch_time_ms() - sleep_start_time_ms);
		if (remaining_time_ms > 10)
			usleep(1000);
		else
			usleep(100);
	}
}
