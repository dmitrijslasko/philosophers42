/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:33:15 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/25 01:53:51 by dmlasko          ###   ########.fr       */
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
	if (!data->simulation_is_on)
		return ;
	if (TAKEN_LEFT_FORK == status)
		printf("%lld >> %lld [%d] has taken a L fork\n", runtime_us, runtime_ms, philo->id);
	else if (TAKEN_RIGHT_FORK == status)
		printf("%lld >> %lld [%d] has taken a R fork\n", runtime_us, runtime_ms, philo->id);
	else if (EATING == status)
		printf("%lld >> %lld [%d] is eating\n", runtime_us, runtime_ms, philo->id);
	else if (SLEEPING == status)
		printf(GREEN"%lld >> %lld [%d] is sleeping\t\tMeals count: %d\n"RST, runtime_us, runtime_ms, philo->id, philo->meals_count);
	else if (THINKING == status)
		printf(YELLOW"%lld >> %lld [%d] is thinking\n"RST, runtime_us, runtime_ms, philo->id);
	else if (DIED == status)
		{
			mutex_operation(&data->data_access_mutex, LOCK);
			data->simulation_is_on = 0;
			mutex_operation(&data->data_access_mutex, UNLOCK);
			printf(RED"%lld >> %lld [%d] died\n"RST, runtime_us, runtime_ms, philo->id);
		}
}

void write_status(t_data *data, t_philosopher *philo, t_status status)
{
	long long runtime;

	mutex_operation(&data->data_access_mutex, LOCK);
	runtime = get_sim_runtime_ms(data);
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
		usleep(DEATH_MSG_TIMEOUT_US);
		printf("%lld %d died\n", runtime, philo->id);
	}
}
