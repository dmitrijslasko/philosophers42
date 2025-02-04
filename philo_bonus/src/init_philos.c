/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 00:17:25 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/04 21:14:43 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * Initializes philosophers.
 */
int	init_philos(t_data *data)
{
	data->philos = safe_malloc(sizeof(t_philosopher));
	data->philos->id = 0;
	data->philos->last_meal_time_ms = 0;
	data->philos->meals_count = 0;
	data->philos->is_alive = 1;
	data->philos->is_full = 0;
	data->philos->data = data;
	return (EXIT_SUCCESS);
}
