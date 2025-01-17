/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 02:14:59 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/17 02:46:13 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Part of the philosopher's routine – thinking.
 */
void philo_think(t_data *data, t_philosopher *philo)
{
	int	time_to_think_ms;
	
	time_to_think_ms = data->time_to_die_ms - data->time_to_eat_ms - data->time_to_sleep_ms;
	if (time_to_think_ms < 0)
		time_to_think_ms *= -1;
	else if (time_to_think_ms < 20)
		time_to_think_ms = 0;
	else
		time_to_think_ms /= 2;
	write_status(data, philo, THINKING);
	msleep(data, time_to_think_ms);
}

/**
 * Part of the philosopher's routine – taking the LEFT fork.
 */
void philo_take_left_fork(t_data *data, t_philosopher *philo)
{
	mutex_operation(&philo->fork_left->fork_mutex, LOCK);
	write_status(data, philo, TAKEN_LEFT_FORK);
}
/**
 * Part of the philosopher's routine – taking the RIGHT fork.
 */
void philo_take_right_fork(t_data *data, t_philosopher *philo)
{
	mutex_operation(&philo->fork_right->fork_mutex, LOCK);
	write_status(data, philo, TAKEN_RIGHT_FORK);
}

/**
 * Part of the philosopher's routine – eating.
 */
void philo_eat(t_data *data, t_philosopher *philo)
{	
	philo->last_meal_time_ms = get_runtime(data);
	write_status(data, philo, EATING);
	msleep(data, data->time_to_eat_ms);
	philo->meals_count++;
}

/**
 * Part of the philosopher's routine – sleeping.
 */
void philo_sleep(t_data *data, t_philosopher *philo)
{
	mutex_operation(&philo->fork_left->fork_mutex, UNLOCK);
	mutex_operation(&philo->fork_right->fork_mutex, UNLOCK);
	write_status(data, philo, SLEEPING);
	msleep(data, data->time_to_sleep_ms);
}

void wait_for_all_threads(t_data *data)
{
	while (1)
	{
		mutex_operation(&data->data_access_mutex, LOCK);
		if(data->all_threads_created)
		{
			mutex_operation(&data->data_access_mutex, UNLOCK);
			break ;
		}
		mutex_operation(&data->data_access_mutex, UNLOCK);
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
	philo->last_meal_time_ms = get_runtime(data);
	mutex_operation(&data->data_access_mutex, LOCK);
	data->simulation_start_time = get_current_time();
	mutex_operation(&data->data_access_mutex, UNLOCK);
	while (data->simulation_is_on)
	{
		if (philo->meals_count == data->no_of_meals_required)
			break ;
		if (philo->id % 2 != 0)
			philo_think(data, philo);
		philo_take_left_fork(data, philo);
		philo_take_right_fork(data, philo);
		philo_eat(data, philo);
		philo_sleep(data, philo);
		if (philo->id % 2 == 0)
			philo_think(data, philo);
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
		data->philo_threads[i] = safe_malloc(sizeof(pthread_t));
		if (!data->philo_threads[i])
			return (MALLOC_FAIL);
		pthread_create(&data->philo_threads[i], NULL, philosopher_routine, (void *)&data->philos[i]);
		if (DEBUG)
			printf("Philo thread [%d] created!\n", i);
		i++;
	}
	return (EXIT_SUCCESS);
}
