/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:46:02 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/04 21:47:08 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int check_philo_status(t_data *data)
{
	data->philos->is_alive = philo_is_alive(data, data->philos);
	data->philos->is_full = philo_is_full(data, data->philos);
	if (data->philos->is_alive == 0)
	{
		write_status(data, data->philos, DIED);
	}
	return (0);
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
	philo->last_meal_time_ms = get_sim_runtime_ms(data);
	write_status(data, philo, EATING);
	msleep(data, data->time_to_eat_ms);
	philo->meals_count++;
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

void	wait_for_all_threads(t_data *data)
{
	//if (SYNC_THREADS)
	//{
	//	while (1)
	//	{
	//		sem_wait(data->sem_data_access);
	//		if (data->simulation_status == 1)
	//		{
	//			sem_post(data->sem_data_access);
	//			break ;
	//		}
	//		sem_post(data->sem_data_access);
	//		usleep(100);
	//	}
	//}
	sem_wait(data->sem_data_access);
	if (data->simulation_start_time_us == 0)
		data->simulation_start_time_us = get_epoch_time_us();
	if (data->simulation_start_time_ms == 0)
		data->simulation_start_time_ms = get_epoch_time_ms();
	sem_post(data->sem_data_access);
}

/**
 * A philosopher's routine.
 */
void	*philosopher_routine(t_data *data)
{
	//puts("Philo routine started!");
	if (data->philos->id % 2 == 0)
		usleep(START_DELAY_US);
	data->philos->last_meal_time_ms = get_sim_runtime_ms(data);
	while (1)
	{
		check_philo_status(data);
		if (philo_take_forks(data, data->philos) == 1)
			return (NULL);
		check_philo_status(data);
		philo_eat(data, data->philos);
		check_philo_status(data);
		philo_sleep(data, data->philos);
	}
	sem_close(data->sem_forks);
	return (NULL);
}
