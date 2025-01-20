/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:33:15 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/20 13:34:46 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *str)
{
	printf(RED"%s"RESET, str);
}

void	write_status_debug(t_data *data, t_philosopher *philo, t_status status)
{
	if (!data->simulation_is_on)
		return ;
	if (TAKEN_LEFT_FORK == status)
		printf("%lld %d has taken a L fork\n", get_simulation_runtime_ms_ms(data), philo->id);
	else if (TAKEN_RIGHT_FORK == status)
		printf("%lld %d has taken a R fork\n", get_simulation_runtime_ms_ms(data), philo->id);
	else if (EATING == status)
		printf("%lld %d is eating\n", get_simulation_runtime_ms_ms(data), philo->id);
	else if (SLEEPING == status)
		printf(GREEN"%lld %d is sleeping\tMeals count: %d\n"RESET, get_simulation_runtime_ms_ms(data), philo->id, philo->meals_count);
	else if (THINKING == status)
		printf(YELLOW"%lld %d is thinking\n"RESET, get_simulation_runtime_ms_ms(data), philo->id);
		else if (DIED == status)
		{
			mutex_operation(&data->data_access_mutex, LOCK);
			data->simulation_is_on = 0;
			mutex_operation(&data->data_access_mutex, UNLOCK);
			printf(RED"%lld %d died\n"RESET, get_simulation_runtime_ms_ms(data), philo->id);
		}
	else
		print_error("Status not recognized...\n");
}

void write_status(t_data *data, t_philosopher *philo, t_status status)
{
	if (DEBUG)
		write_status_debug(data, philo, status);
	mutex_operation(&data->status_write_mutex, LOCK);
	if (!data->simulation_is_on)
	{
		mutex_operation(&data->status_write_mutex, UNLOCK);
		return ;
	}
	if (TAKEN_LEFT_FORK == status || TAKEN_RIGHT_FORK == status)
		printf("%lld %d has taken a fork\n", get_simulation_runtime_ms_ms(data), philo->id);
	else if (EATING == status)
		printf("%lld %d is eating\n", get_simulation_runtime_ms_ms(data), philo->id);
	else if (SLEEPING == status)
		printf("%lld %d is sleeping\n", get_simulation_runtime_ms_ms(data), philo->id);
	else if (THINKING == status)
		printf("%lld %d is thinking\n", get_simulation_runtime_ms_ms(data), philo->id);
	else if (DIED == status)
	{
		mutex_operation(&data->data_access_mutex, LOCK);
		data->simulation_is_on = 0;
		mutex_operation(&data->data_access_mutex, UNLOCK);
		printf("%lld %d died\n", get_simulation_runtime_ms_ms(data), philo->id);
	}
	else
		print_error("Status not recognized...\n");
	mutex_operation(&data->status_write_mutex, UNLOCK);
}
