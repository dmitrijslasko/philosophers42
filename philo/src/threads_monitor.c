/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:57:42 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/31 17:57:43 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * This function сhecks and announces philo's death if it happens.
 * @param *data table info
 * @param *philo philosopher
 */
int	philo_is_alive(t_data *data, t_philosopher *philo)
{
	int	last_meal_ms;
	int	response;

	response = 1;
	mutex_operation(data->data_access_mutex, LOCK);
	last_meal_ms = philo->last_meal_time_ms;
	if (get_sim_runtime_ms(data) - last_meal_ms > data->time_to_die_ms)
		response = 0;
	mutex_operation(data->data_access_mutex, UNLOCK);
	return (response);
}

int	all_philos_are_alive(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_of_philos)
	{
		if (philo_is_alive(data, &data->philos[i]) == 0)
		{
			write_status(data, &data->philos[i], DIED);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	philo_is_full(t_data *data, t_philosopher *philo)
{
	int	response;

	response = 0;
	mutex_operation(&philo->philo_data_access_mutex, LOCK);
	if (philo->meals_count >= data->no_of_meals_required)
		response = 1;
	mutex_operation(&philo->philo_data_access_mutex, UNLOCK);
	return (response);
}

int	all_philos_are_full(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_of_philos)
	{
		if (philo_is_full(data, &data->philos[i]) != 1)
			return (FALSE);
		i++;
	}
	set_protected_value(data, &data->simulation_status, 0);
	return (TRUE);
}

/**
 * A monitor thread routine.
 */
void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = arg;
	wait_for_all_threads(data);
	while (all_philos_are_alive(data)
		&& (!all_philos_are_full(data) || data->no_of_meals_required == -1))
		usleep(MONITOR_FREQ_US);
	return (NULL);
}

/**
 * Wrapper for pthread_create() function.
 */
int	create_monitor(t_data *data)
{
	pthread_create(&data->monitor_thread, NULL, monitor_routine, (void *)data);
	if (DEBUG)
		printf(B_MAGENTA">>>>>>>>>>>>>> MONITOR THREAD CREATED\n"RST);
	set_protected_value(data, &data->simulation_status, 1);
	return (EXIT_SUCCESS);
}

void	join_monitor_thread(t_data *data)
{
	pthread_join(data->monitor_thread, NULL);
}
