/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 02:14:59 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/15 16:09:14 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status_debug(t_data *data, t_philosopher *philo, t_status status)
{
	if (TAKEN_LEFT_FORK == status)
		printf("%lld %d has taken a L fork\n", get_runtime(data), philo->id);
	else if (TAKEN_RIGHT_FORK == status)
		printf("%lld %d has taken a R fork\n", get_runtime(data), philo->id);
	else if (EATING == status)
		printf("%lld %d is eating\n", get_runtime(data), philo->id);
	else if (SLEEPING == status)
		printf(GREEN"%lld %d is sleeping\tMeals count: %d\n"RESET, get_runtime(data), philo->id, philo->meals_count);
	else if (THINKING == status)
		printf(YELLOW"%lld %d is thinking\n"RESET, get_runtime(data), philo->id);
	else
		print_error("Status not recognized...\n");
}

void	write_status(t_data *data, t_philosopher *philo, t_status status)
{
	if (DEBUG)
		write_status_debug(data, philo, status);
	else
	{
		if (TAKEN_LEFT_FORK == status)
			printf("%lld %d has taken a fork\n", get_runtime(data), philo->id);
		else if (TAKEN_RIGHT_FORK == status)
			printf("%lld %d has taken a fork\n", get_runtime(data), philo->id);
		else if (EATING == status)
			printf("%lld %d is eating\n", get_runtime(data), philo->id);
		else if (SLEEPING == status)
			printf("%lld %d is sleeping\n", get_runtime(data), philo->id);
		else if (THINKING == status)
			printf("%lld %d is thinking\n", get_runtime(data), philo->id);
		else
			print_error("Status not recognized...\n");
	}
}
/**
 * Part of the philosopher's routine – thinking.
 */
void philo_think(t_data *data, t_philosopher *philo)
{
	int	time_to_think_ms;
	
	if (!data->simulation_is_on)
		return ;
	time_to_think_ms = data->time_to_die_ms - data->time_to_eat_ms - data->time_to_sleep_ms;
	if (time_to_think_ms != 0)
	{
		time_to_think_ms /= 5;
		safe_mutex_operation(&data->status_write_mutex, LOCK);
		write_status(data, philo, THINKING);
		safe_mutex_operation(&data->status_write_mutex, UNLOCK);
		msleep(time_to_think_ms);
	}
}

/**
 * Part of the philosopher's routine – taking the LEFT fork.
 */
void philo_take_left_fork(t_data *data, t_philosopher *philo)
{
	while (philo->fork_left->fork_is_taken)
	{
		if (!data->simulation_is_on)
			continue ;
		break ;
	}
	safe_mutex_operation(&philo->fork_left->fork_mutex, LOCK);
	philo->fork_left->fork_is_taken = 1;
	safe_mutex_operation(&data->status_write_mutex, LOCK);
	write_status(data, philo, TAKEN_LEFT_FORK);
	safe_mutex_operation(&data->status_write_mutex, UNLOCK);
}
/**
 * Part of the philosopher's routine – taking the RIGHT fork.
 */
void philo_take_right_fork(t_data *data, t_philosopher *philo)
{
	while (philo->fork_right->fork_is_taken)
	{
		if (!data->simulation_is_on)
			continue ;
		break ;
	}
	safe_mutex_operation(&philo->fork_right->fork_mutex, LOCK);
	philo->fork_right->fork_is_taken = 1;
	safe_mutex_operation(&data->status_write_mutex, LOCK);
	write_status(data, philo, TAKEN_RIGHT_FORK);
	safe_mutex_operation(&data->status_write_mutex, UNLOCK);
}

/**
 * Part of the philosopher's routine – eating.
 */
void philo_eat(t_data *data, t_philosopher *philo)
{
	if(!data->simulation_is_on)
		return ;
	philo->last_meal_time_ms = get_runtime(data);
	safe_mutex_operation(&data->status_write_mutex, LOCK);
	write_status(data, philo, EATING);
	safe_mutex_operation(&data->status_write_mutex, UNLOCK);
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
	safe_mutex_operation(&data->status_write_mutex, LOCK);
	write_status(data, philo, SLEEPING);
	safe_mutex_operation(&data->status_write_mutex, UNLOCK);
	safe_mutex_operation(&philo->fork_left->fork_mutex, UNLOCK);
	safe_mutex_operation(&philo->fork_right->fork_mutex, UNLOCK);
	msleep(data->time_to_sleep_ms);
}

void wait_for_all_threads(t_data *data)
{
	while (1)
	{
		safe_mutex_operation(&data->data_access_mutex, LOCK);
		if(data->all_threads_created)
		{
			safe_mutex_operation(&data->data_access_mutex, UNLOCK);
			break ;
		}
		safe_mutex_operation(&data->data_access_mutex, UNLOCK);
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
	safe_mutex_operation(&data->data_access_mutex, LOCK);
	data->simulation_start_time = get_current_time();
	safe_mutex_operation(&data->data_access_mutex, UNLOCK);
	while (data->simulation_is_on)
	{
		if (philo->meals_count == data->no_of_meals_required)
			break ;
		if (philo->id % 2 != 0)
			usleep(100);
		// {
		// 	philo_take_left_fork(data, philo);
		// 	philo_take_right_fork(data, philo);
		// }
		// else
		// {
		philo_take_left_fork(data, philo);
		philo_take_right_fork(data, philo);
		// }
		philo_eat(data, philo);
		philo_sleep(data, philo);
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
