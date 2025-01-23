/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:33:15 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/24 00:27:02 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *str)
{
	printf(RED"%s"RESET, str);
}

void	write_status_debug(t_data *data, t_philosopher *philo, t_status status)
{
	long long runtime_us;
	long long runtime_ms;

	runtime_us = get_simulation_runtime_us(data);
	runtime_ms = get_simulation_runtime_ms(data);
	if (!data->simulation_is_on)
		return ;
	if (TAKEN_LEFT_FORK == status)
		printf("%lld >> %lld [%d] has taken a L fork\n", runtime_us, runtime_ms, philo->id);
	else if (TAKEN_RIGHT_FORK == status)
		printf("%lld >> %lld [%d] has taken a R fork\n", runtime_us, runtime_ms, philo->id);
	else if (EATING == status)
		printf("%lld >> %lld [%d] is eating\n", runtime_us, runtime_ms, philo->id);
	else if (SLEEPING == status)
		printf(GREEN"%lld >> %lld [%d] is sleeping\t\tMeals count: %d\n"RESET, runtime_us, runtime_ms, philo->id, philo->meals_count);
	else if (THINKING == status)
		printf(YELLOW"%lld >> %lld [%d] is thinking\n"RESET, runtime_us, runtime_ms, philo->id);
	else if (DIED == status)
		{
			mutex_operation(&data->data_access_mutex, LOCK);
			data->simulation_is_on = 0;
			mutex_operation(&data->data_access_mutex, UNLOCK);
			printf(RED"%lld >> %lld [%d] died\n"RESET, runtime_us, runtime_ms, philo->id);
		}
	else
		print_error("Status not recognized...\n");
}

void write_status(t_data *data, t_philosopher *philo, t_status status)
{
	long long runtime;

	mutex_operation(&data->data_access_mutex, LOCK);
	runtime = get_simulation_runtime_ms(data);
	if (!data->simulation_is_on)
	{
		mutex_operation(&data->data_access_mutex, UNLOCK);
		return ;
	}
	mutex_operation(&data->data_access_mutex, UNLOCK);
	if (DEBUG)
	{
		write_status_debug(data, philo, status);
		return ;
	}
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
			mutex_operation(&data->data_access_mutex, LOCK);
			data->simulation_is_on = 0;
			mutex_operation(&data->data_access_mutex, UNLOCK);
			usleep(5000);
			printf("%lld %d died\n", runtime, philo->id);
		}
	else
		print_error("Status not recognized...\n");
}
