/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:59:09 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/11 14:49:59 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_is_full(t_data *data, t_philosopher *philo);

/**
 * This function сhecks and announces philo's death if it happens.
 * @param *data table info
 * @param *philo philosopher
 */
int philo_is_alive(t_data *data, t_philosopher *philo)
{
	int	ms_time;

	ms_time = philo->last_meal_time_ms;
	if (get_simulation_runtime_ms(data) - ms_time >= data->time_to_die_ms)
	{
		return (FALSE);
	}
	return (TRUE);
}


int all_philos_are_alive(t_data *data)
{
	int i;

	i = 0;
	while (i < data->no_of_philosophers)
	{
		if (philo_is_alive(data, &data->philos[i]) == 0)
		{
			write_status(data, &data->philos[i], DIED);
			mutex_operation(&data->data_access_mutex, LOCK);
			data->simulation_is_on = 0;
			mutex_operation(&data->data_access_mutex, UNLOCK);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
int	philo_is_full(t_data *data, t_philosopher *philo)
{
	int	philo_is_full;

	philo_is_full = 0;
	mutex_operation(&data->data_access_mutex, LOCK);
	if (philo->meals_count >= data->no_of_meals_required)
		philo_is_full = 1;
	mutex_operation(&data->data_access_mutex, UNLOCK);
	return (philo_is_full);
}

int all_philos_are_full(t_data *data)
{
	int i;

	i = 0;
	while (i < data->no_of_philosophers)
	{
		if (philo_is_full(data, &data->philos[i]) != 1)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/**
 * A monitor thread routine.
 */
void *monitor_routine(void *arg)
{
	t_data *data;

	data = arg;
	wait_for_all_threads(data);
	while (all_philos_are_alive(data)
			&& (!all_philos_are_full(data) || data->no_of_meals_required < 0))
		usleep(MONITOR_FREQ_US);
	mutex_operation(&data->data_access_mutex, LOCK);
	data->simulation_is_on = 0;
	mutex_operation(&data->data_access_mutex, UNLOCK);
    return (NULL);
}

/**
 * Wrapper for pthread_create() function.
 */
int	create_monitor(t_data *data)
{
	pthread_create(&data->monitor_thread, NULL, monitor_routine, (void *)data);
	if (DEBUG)
		printf(B_MAGENTA">>>>>>>>>>>>>> MONITOR THREAD CREATED\n"RESET);
	mutex_operation(&data->data_access_mutex, LOCK);
	data->all_threads_created = 1;
	data->simulation_start_time_us = get_epoch_time_us();
	data->simulation_start_time_ms = get_epoch_time_ms();
	data->simulation_is_on = 1;
	mutex_operation(&data->data_access_mutex, UNLOCK);
	return (EXIT_SUCCESS);
}

void join_monitor_thread(t_data *data)
{
	pthread_join(data->monitor_thread, NULL);
}
