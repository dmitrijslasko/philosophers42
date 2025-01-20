/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:46:02 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/20 14:53:22 by dmlasko          ###   ########.fr       */
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
void philo_take_forks(t_data *data, t_philosopher *philo)
{
	if (data->no_of_philosophers == 1 && philo->fork_left->fork_taken)
		return ;
	write_status(data, philo, THINKING);
	while (philo->fork_left->fork_taken == 1)
		usleep(FORK_HUNT_DELAY_US);
	mutex_operation(&philo->fork_left->fork_mutex, LOCK);
	philo->fork_left->fork_taken = 1;
	mutex_operation(&philo->fork_left->fork_mutex, UNLOCK);
	write_status(data, philo, TAKEN_LEFT_FORK);
	if (data->no_of_philosophers == 1)
		return ;
	while (philo->fork_right->fork_taken == 1)
		usleep(FORK_HUNT_DELAY_US);
	mutex_operation(&philo->fork_right->fork_mutex, LOCK);
	philo->fork_right->fork_taken = 1;
	mutex_operation(&philo->fork_right->fork_mutex, UNLOCK);
	write_status(data, philo, TAKEN_RIGHT_FORK);

}

/**
 * Part of the philosopher's routine – eating.
 */
void philo_eat(t_data *data, t_philosopher *philo)
{
	if (data->no_of_philosophers == 1)
		return ;
	philo->last_meal_time_ms = get_simulation_runtime_ms_ms(data);
	write_status(data, philo, EATING);
	msleep(data, data->time_to_eat_ms);
	mutex_operation(&data->data_access_mutex, LOCK);
	philo->meals_count++;
	mutex_operation(&data->data_access_mutex, UNLOCK);
}

/**
 * Part of the philosopher's routine – sleeping.
 */
void philo_sleep(t_data *data, t_philosopher *philo)
{
	if (data->no_of_philosophers == 1)
		return ;
	mutex_operation(&philo->fork_left->fork_mutex, LOCK);
	philo->fork_left->fork_taken = 0;
	mutex_operation(&philo->fork_left->fork_mutex, UNLOCK);
	mutex_operation(&philo->fork_right->fork_mutex, LOCK);
	philo->fork_right->fork_taken = 0;
	mutex_operation(&philo->fork_right->fork_mutex, UNLOCK);
	write_status(data, philo, SLEEPING);
	msleep(data, data->time_to_sleep_ms);
}

void wait_for_all_threads(t_data *data)
{
	int	wait_is_on;

	wait_is_on = 1;
	while (wait_is_on)
	{
		mutex_operation(&data->data_access_mutex, LOCK);
		if(data->all_threads_created)
			wait_is_on = 0;
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
	philo->last_meal_time_ms = get_simulation_runtime_ms_ms(data);
	mutex_operation(&data->data_access_mutex, LOCK);
	data->simulation_start_time_ms = get_epoch_time();
	mutex_operation(&data->data_access_mutex, UNLOCK);
	if (philo->id % 2 == 0)
		usleep(THREAD_START_DELAY_US);
	while (data->simulation_is_on)
	{
		philo_take_forks(data, philo);
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
			printf("Philo thread [%d] created!\n", i);
		i++;
	}
	return (EXIT_SUCCESS);
}
