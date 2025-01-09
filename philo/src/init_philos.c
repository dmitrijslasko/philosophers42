/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 00:17:25 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/09 15:02:21 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int init_philos(t_data *data)
{
	int	i;
	data->philos = malloc(data->philosophers_len * sizeof(t_philosopher));
	if (data->philos == NULL)
		return (MALLOC_FAIL);
	
	i = 0;
	while (i < data->philosophers_len)
	{
		data->philos[i].id = i + 1;
		data->philos[i].is_alive = 1;
		data->philos[i].last_meal_time_ms = get_runtime(data);
		
		data->philos[i].fork_left = &data->forks[i];
		data->philos[i].fork_right = &data->forks[(i + 1) % data->philosophers_len];
		// printf("%lld: Philosopher %d initialized.\n", get_runtime(data), data->philos[i].id);
		data->philos[i].data = data;
		i++;
	}
	data->threads = malloc(data->philosophers_len * sizeof(pthread_t));
	
	return (EXIT_SUCCESS);
}
