/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:21:32 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/20 16:37:06 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msleep(t_data *data, unsigned int sleep_time_ms)
{
	(void)data;
	long long	sleep_start_time_ms;

	sleep_start_time_ms = get_epoch_time();
	while (get_epoch_time() - sleep_start_time_ms < sleep_time_ms)
	{
		usleep(CUSTOM_SLEEP_PERIOD_US);
		// total_sleep_timer += CUSTOM_SLEEP_PERIOD_US;
		// printf(YELLOW"%lld - %lld = %lld < %d \n"RESET, get_epoch_time2(), sleep_start_time_ms, get_epoch_time2() - sleep_start_time_ms, sleep_time_ms);

	}
	// printf(YELLOW"%lld - %lld = %lld < %d \n"RESET, get_epoch_time(), sleep_start_time_ms, get_epoch_time() - sleep_start_time_ms, sleep_time_ms);
	// printf(YELLOW"TOTAL SLEEP TIMER: %d\n"RESET, total_sleep_timer);
}
