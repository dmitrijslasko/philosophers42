/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:59:09 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/09 17:53:04 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_life(t_data *data, t_philosopher *philo)
{
	if (get_runtime(data) - philo->last_meal_time_ms >= data->time_to_die)
	{
		printf(RED"%lld %d is dead\n"RESET, get_runtime(data), philo->id);
		exit (1);
	}
	return (0);
}
void think(t_data *data, t_philosopher *philo)
{
	int	time_to_think;

	time_to_think = data->time_to_die - data->time_to_eat - data->time_to_sleep;
	time_to_think /= 2;
	check_life(data, philo);
	printf("%lld %d is thinking\n", get_runtime(data), philo->id);
	usleep(time_to_think);
}

void take_left_fork(t_data *data, t_philosopher *philo)
{
	check_life(data, philo);
	printf("%lld %d has taken a L fork\n", get_runtime(data), philo->id);
	pthread_mutex_lock(philo->fork_left);

}
void take_right_fork(t_data *data, t_philosopher *philo)
{
	check_life(data, philo);
	printf(YELLOW"%lld %d has taken a R fork\n"RESET, get_runtime(data), philo->id);
	pthread_mutex_lock(philo->fork_right);
	philo->last_meal_time_ms = get_runtime(data);
}

void eat(t_data *data, t_philosopher *philo)
{
	check_life(data, philo);
	printf("%lld %d is eating\n", get_runtime(data), philo->id);
	usleep(data->time_to_eat);
}

void sleep_tight(t_data *data, t_philosopher *philo)
{
	check_life(data, philo);
	printf("%lld %d is sleeping\n", get_runtime(data), philo->id);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	usleep(data->time_to_sleep);
}

void *philosopher_routine(void *arg)
{
	t_philosopher *philo;
	t_data	*data;
	int	round_counter;

	round_counter = 0;

	philo = (t_philosopher *)arg;
	data = philo->data;
	while (1 == 1)
	{
		if (round_counter == data->number_of_times_each_philosopher_must_eat)
			break ;
		take_left_fork(data, philo);
		take_right_fork(data, philo);
		eat(data, philo);
		sleep_tight(data, philo);
		think(data, philo);
		round_counter++;
	}
    return (NULL);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philosophers_len)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}
int	start_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philosophers_len)
	{
		data->threads[i] = malloc(sizeof(pthread_t));
		if (!data->threads[i])
			return (MALLOC_FAIL);
		pthread_create(&data->threads[i], NULL, philosopher_routine, (void *)&data->philos[i]);
		// usleep(100);
		i++;
	}
	return (EXIT_SUCCESS);
}
