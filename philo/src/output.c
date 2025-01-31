/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:33:15 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/31 00:05:44 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *str, int error_code)
{
	printf(RED"%s"RST, str);
	return (error_code);
}

void	write_status_debug(t_data *data, t_philosopher *philo, t_status status)
{
	long long	runtime_us;
	long long	runtime_ms;

	runtime_us = get_sim_runtime_us(data);
	runtime_ms = get_sim_runtime_ms(data);
	mutex_operation(data->print_mutex, LOCK);
	if (data->simulation_is_on)
	{
		if (TAKEN_LEFT_FORK == status)
			printf(DEBUG_LEFT_FORK, runtime_us, runtime_ms, philo->id);
		else if (TAKEN_RIGHT_FORK == status)
			printf(DEBUG_RIGHT_FORK, runtime_us, runtime_ms, philo->id);
		else if (EATING == status)
			printf(DEBUG_EAT, runtime_us, runtime_ms, philo->id);
		else if (SLEEPING == status)
			printf(DEBUG_SLEEP, runtime_us, runtime_ms, philo->id, philo->meals_count);
		else if (THINKING == status)
			printf(DEBUG_THINK, runtime_us, runtime_ms, philo->id);
		else if (DIED == status)
		{
			mutex_operation(data->data_access_mutex, LOCK);
			data->simulation_is_on = 0;
			mutex_operation(data->data_access_mutex, UNLOCK);
			printf(DEBUG_DIED, runtime_us, runtime_ms, philo->id);
		}
	}
	mutex_operation(data->print_mutex, UNLOCK);
}

void	write_status(t_data *data, t_philosopher *philo, t_status status)
{
	long long	runtime;

	mutex_operation(data->data_access_mutex, LOCK);
	runtime = get_sim_runtime_ms(data);
	if (!data->simulation_is_on)
	{
		mutex_operation(data->data_access_mutex, UNLOCK);
		return ;
	}
	mutex_operation(data->data_access_mutex, UNLOCK);
	if (DEBUG)
	{
		write_status_debug(data, philo, status);
		return ;
	}
	mutex_operation(data->print_mutex, LOCK);
	if (data->simulation_is_on)
	{
		if (TAKEN_LEFT_FORK == status || TAKEN_RIGHT_FORK == status)
			printf("%lld %d has taken a fork\n", runtime, philo->id);
		else if (EATING == status)
			printf("%lld %d is eating\n", runtime, philo->id);
		else if (SLEEPING == status)
			printf("%lld %d is sleeping\n", runtime, philo->id);
		else if (THINKING == status)
			printf("%lld %d is thinking\n", runtime, philo->id);
		else if (DIED == status)
		{
			mutex_operation(data->data_access_mutex, LOCK);
			data->simulation_is_on = 0;
			mutex_operation(data->data_access_mutex, UNLOCK);
			printf("%lld %d died\n", runtime, philo->id);
		}
	}
	mutex_operation(data->print_mutex, UNLOCK);
}
