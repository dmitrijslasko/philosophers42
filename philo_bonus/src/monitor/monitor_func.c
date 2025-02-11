/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:57:42 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/10 23:02:41 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * Checks if a philospher is still alive.
 */
int	philo_is_alive(t_data *data, t_philosopher *philo)
{
	int	last_meal_ms;
	int	response;

	response = 1;
	last_meal_ms = philo->last_meal_time_ms;
	if (get_sim_runtime_ms(data) - last_meal_ms > data->time_to_die_ms)
		response = 0;
	return (response);
}

/**
 * Checks if a philospher is full (has has enough food).
 */
int	philo_is_full(t_data *data, t_philosopher *philo)
{
	int	response;

	response = 0;
	if (philo->meals_count >= data->no_of_meals_required && \
				data->no_of_meals_required > 0)
		response = 1;
	return (response);
}

