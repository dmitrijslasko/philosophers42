/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:21:32 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/15 01:05:41 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msleep(unsigned int sleep_time_ms)
{
	long long	simulation_start_time;

	simulation_start_time = get_current_time();
	while (get_current_time() - simulation_start_time < sleep_time_ms)
		usleep(500);
}