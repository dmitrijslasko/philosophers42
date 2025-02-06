/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 00:17:25 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/06 17:40:00 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * Initializes philosophers.
 */
int	init_philos(t_data *data)
{
	int i;

	data->philos = safe_malloc(data->no_of_philos * sizeof(t_philosopher));
	i = 0;
	while (i < data->no_of_philos)
	{
		data->philos.id = i + 1;
		printf("Philo [%d] created! ID: [%d]\n", i, data->philos.id);
		data->philos.last_meal_time_ms = 0;
		data->philos.meals_count = 0;
		data->philos.is_alive = 1;
		data->philos.is_full = 0;
		//data->philos->data = data;
		i++;
	}
	return (EXIT_SUCCESS);
}
