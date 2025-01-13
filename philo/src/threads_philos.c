/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 02:14:59 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/13 23:40:27 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Part of the philosopher's routine – thinking.
 */
void philo_think(t_data *data, t_philosopher *philo)
{
	int	time_to_think_ms;
	
	if(!data->simulation_is_on)
		return ;
	time_to_think_ms = data->time_to_die_ms - data->time_to_eat_ms - data->time_to_sleep_ms;
	printf("%lld %d is thinking\n", get_runtime(data), philo->id);
	msleep(time_to_think_ms);
}

/**
 * Part of the philosopher's routine – taking the LEFT fork.
 */
void philo_take_left_fork(t_data *data, t_philosopher *philo)
{
	while (philo->fork_left->fork_is_taken && data->simulation_is_on)
		continue ;
	if(!data->simulation_is_on)
		return ;
	pthread_mutex_lock(&philo->fork_left->fork_mutex);
	philo->fork_left->fork_is_taken = 1;
	printf("%lld %d has taken a L fork\n", get_runtime(data), philo->id);
}
/**
 * Part of the philosopher's routine – taking the RIGHT fork.
 */
void philo_take_right_fork(t_data *data, t_philosopher *philo)
{
	while (philo->fork_right->fork_is_taken && data->simulation_is_on)
		continue ;
	if(!data->simulation_is_on)
		return ;
	pthread_mutex_lock(&philo->fork_right->fork_mutex);
	philo->fork_right->fork_is_taken = 1;
	printf(YELLOW"%lld %d has taken a R fork\n"RESET, get_runtime(data), philo->id);
}

/**
 * Part of the philosopher's routine – eating.
 */
void philo_eat(t_data *data, t_philosopher *philo)
{
	if(!data->simulation_is_on)
		return ;
	philo->last_meal_time_ms = get_runtime(data);
	printf("%lld %d is eating\n", get_runtime(data), philo->id);
	msleep(data->time_to_eat_ms);
	philo->meals_count++;
}

/**
 * Part of the philosopher's routine – sleeping.
 */
void philo_sleep(t_data *data, t_philosopher *philo)
{
	if(!data->simulation_is_on)
		return ;
	if (EXTENDED_OUTPUT)
		printf(GREEN"%lld %d is sleeping. Meals count: %d\n"RESET, get_runtime(data), philo->id, philo->meals_count);
	else
		printf("%lld %d is sleeping.\n", get_runtime(data), philo->id);
	pthread_mutex_unlock(&philo->fork_left->fork_mutex);
	philo->fork_left->fork_is_taken = 0;
	pthread_mutex_unlock(&philo->fork_right->fork_mutex);
	philo->fork_right->fork_is_taken = 0;
	msleep(data->time_to_sleep_ms);
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
	while (data->simulation_is_on)
	{
		if (philo->meals_count == data->no_of_meals_required)
			break ;
		philo_take_left_fork(data, philo);
		if (data->no_of_philosophers > 1)
		{
			philo_take_right_fork(data, philo);
			philo_eat(data, philo);
			philo_sleep(data, philo);
			philo_think(data, philo);
		}
		else
			break;
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
int	start_philo_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_of_philosophers)
	{
		data->philo_threads[i] = malloc(sizeof(pthread_t));
		if (!data->philo_threads[i])
			return (MALLOC_FAIL);
		pthread_create(&data->philo_threads[i], NULL, philosopher_routine, (void *)&data->philos[i]);
		printf("Thread started!\n");
		i++;
	}
	return (EXIT_SUCCESS);
}
