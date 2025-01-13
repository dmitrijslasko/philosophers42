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

/**
 * This function сhecks and announces philo's death if it happens.
 * @param *data table info
 * @param *philo philosopher
 */
int philo_is_alive(t_data *data, t_philosopher *philo)
{
	if (get_runtime(data) - philo->last_meal_time_ms >= data->time_to_die_ms)
	{
		philo->is_alive = 0;
		return (FALSE);
	}
	return (TRUE);
}

void join_monitor_thread(t_data *data)
{
	pthread_join(data->monitor_thread, NULL);
}

int all_philos_are_alive(t_data *data)
{
	int i;
	
	i = 0;
	while (i < data->no_of_philosophers)
	{
		if (philo_is_alive(data, &data->philos[i]) == 0)
		{
			printf(RED "%lld %d is dead\n" RESET, get_runtime(data), data->philos[i].id);
			data->simulation_is_on = 0;
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
int all_philos_ate_enough(t_data *data)
{
	int i;
	int	no_of_meals_actual;

	i = 0;
	while (i < data->no_of_philosophers)
	{
		no_of_meals_actual = data->philos[i].meals_count;
		if (no_of_meals_actual < data->no_of_meals_required)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
/**
 * A monitor's routine.
 */
void *monitor_routine(void *arg)
{
	t_data *data;
	
	data = arg;
	while (all_philos_are_alive(data) && !all_philos_ate_enough(data))
	{
		// printf("MONITOR...\n");
		usleep(10);
	}
	data->simulation_is_on = 0;
    return (NULL);
}

/**
 * Wrapper for pthread_create() function.
 */
int	start_monitor(t_data *data)
{
	pthread_create(&data->monitor_thread, NULL, monitor_routine, (void *)data);
	return (EXIT_SUCCESS);
}
