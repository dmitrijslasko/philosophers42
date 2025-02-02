/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 00:17:25 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/03 00:40:21 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Initializes philosophers.
 */
int	init_philos(t_data *data)
{
	int	i;

	data->philos = safe_malloc(data->no_of_philos * sizeof(t_philosopher));
	if (data->philos == NULL)
		return (MALLOC_FAIL);
	i = 0;
	while (i < data->no_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal_time_ms = 0;
		data->philos[i].meals_count = 0;
		data->philos[i].fork_left = &data->forks[i];
		data->philos[i].fork_right = &data->forks[(i + 1) % data->no_of_philos];
		if (DEBUG)
			printf(GREEN "Philo [%d] initialized.\n" RST, data->philos[i].id);
		data->philos[i].data = data;
		i++;
	}
	return (EXIT_SUCCESS);
}
