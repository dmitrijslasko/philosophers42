/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 00:17:25 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/06 18:01:27 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * Initializes philosophers.
 */
int	init_philos(t_data *data)
{
	int i;

	data->philos = safe_malloc(sizeof(t_philosopher) * data->no_of_philos);
	i = 0;
	while (i < data->no_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal_time_ms = 0;
		data->philos[i].meals_count = 0;
		data->philos[i].is_alive = 1;
		data->philos[i].is_full = 0;
		printf("Philo [%d] created! ID: [%d]\n", i, data->philos[i].id);
		i++;
	}
	return (EXIT_SUCCESS);
}
