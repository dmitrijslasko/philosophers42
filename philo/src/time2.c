/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:32:44 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/31 18:11:51 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_sim_runtime_us(t_data *data)
{
	long long	runtime_us;

	runtime_us = 0;
	mutex_operation(data->data_access_mutex, LOCK);
	runtime_us = get_epoch_time_us() - data->simulation_start_time_us;
	mutex_operation(data->data_access_mutex, UNLOCK);
	return (runtime_us);
}
