/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:46:02 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/22 21:18:05 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Part of the philosopher's routine – taking the LEFT fork.
 */
int philo_take_forks(t_data *data, t_philosopher *philo)
{
	write_status(data, philo, THINKING);
	mutex_operation(philo->fork_left, LOCK);
	write_status(data, philo, TAKEN_LEFT_FORK);
	if (data->no_of_philosophers == 1)
		return (1);
	mutex_operation(philo->fork_right, LOCK);
	write_status(data, philo, TAKEN_RIGHT_FORK);
	return (0);
}

/**
 * Part of the philosopher's routine – eating.
 */
void philo_eat(t_data *data, t_philosopher *philo)
{
	write_status(data, philo, EATING);
	philo->last_meal_time_ms = get_simulation_runtime_ms(data);
	msleep(data, data->time_to_eat_ms);
	philo->meals_count++;
	mutex_operation(philo->fork_left, UNLOCK);
	mutex_operation(philo->fork_right, UNLOCK);
}

/**
 * Part of the philosopher's routine – sleeping.
 */
void philo_sleep(t_data *data, t_philosopher *philo)
{
	write_status(data, philo, SLEEPING);
	msleep(data, data->time_to_sleep_ms);
}

void wait_for_all_threads(t_data *data)
{
	while (1)
	{
		if(data->all_threads_created)
		{
			mutex_operation(&data->data_access_mutex, LOCK);
			data->simulation_start_time_us = get_epoch_time_us();
			data->simulation_start_time_ms = get_epoch_time_ms();
			mutex_operation(&data->data_access_mutex, UNLOCK);
			break ;
		}
		usleep(10);
	}
}

/**
 * A philosopher's routine.
 */
void *philosopher_routine(void *arg)
{
	t_philosopher *philo;
	t_data	*data;

	philo = (t_philosopher *)arg;
	data = philo->data;
	wait_for_all_threads(data);
	if (philo->id % 2 == 0)
		msleep(data, data->thread_start_delay_ms);
	philo->last_meal_time_ms = get_simulation_runtime_ms(data);
	while (data->simulation_is_on)
	{
		if (philo_take_forks(data, philo) == 1)
			return (NULL);
		philo_eat(data, philo);
		philo_sleep(data, philo);
	}
    return (NULL);
}

/**
 * Wrapper for pthread_join() function.
 */
int	join_philo_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_of_philosophers)
	{
		pthread_join(data->philo_threads[i], NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * Wrapper for pthread_create() function.
 */
int	create_philo_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_of_philosophers)
	{
		data->philo_threads[i] = (pthread_t)safe_malloc(sizeof(pthread_t));
		if (!data->philo_threads[i])
			return (MALLOC_FAIL);
		pthread_create(&data->philo_threads[i], NULL, philosopher_routine, (void *)&data->philos[i]);
		if (DEBUG)
			printf("Philo thread [%d] created!\n", data->philos[i].id);
		i++;
	}
	return (EXIT_SUCCESS);
}
