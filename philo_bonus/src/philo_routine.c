/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:46:02 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/06 20:05:16 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_philo_status(void *args)
{
	t_data *data;

	data = (t_data *)args;
	while (data->philos->is_alive && data->philos->is_full == 0)
	{
		data->philos->is_alive = philo_is_alive(data, data->philos);
		data->philos->is_full = philo_is_full(data, data->philos);
		usleep(100);
	}
	free(data->process_pids);
	sem_close(data->sem_forks);
	sem_close(data->sem_print);
	free(data->philos);
	exit (EXIT_SUCCESS);
	//return NULL;
}
/**
 * Part of the philosopher's routine – taking the LEFT fork.
 */
int	philo_take_forks(t_data *data, t_philosopher *philo)
{
	write_status(data, philo, THINKING);
	sem_wait(data->sem_forks);
	write_status(data, philo, TAKEN_LEFT_FORK);
	sem_wait(data->sem_forks);
	write_status(data, philo, TAKEN_RIGHT_FORK);
	return (0);
}

/**
 * Part of the philosopher's routine – eating.
 */
void	philo_eat(t_data *data, t_philosopher *philo)
{
	data->philos->last_meal_time_ms = get_sim_runtime_ms(data);
	write_status(data, philo, EATING);
	msleep(data, data->time_to_eat_ms);
	data->philos->meals_count++;
	sem_post(data->sem_forks);
	sem_post(data->sem_forks);
}

/**
 * Part of the philosopher's routine – sleeping.
 */
void	philo_sleep(t_data *data, t_philosopher *philo)
{
	write_status(data, philo, SLEEPING);
	msleep(data, data->time_to_sleep_ms);
}

/**
 * A philosopher's routine.
 */
void	*philosopher_routine(t_data *data)
{
	t_philosopher *philos;

	philos = &data->philos[data->philo_index];
	if (philos->id % 2 == 0)
		usleep(START_DELAY_US);
	philos->last_meal_time_ms = get_sim_runtime_ms(data);
	while (1)
	{
		if (philo_take_forks(data, philos) == 1)
			return (NULL);
		philo_eat(data, philos);
		philo_sleep(data, philos);
	}
	return (NULL);
}
