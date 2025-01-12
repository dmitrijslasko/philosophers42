/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 00:17:25 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/11 17:00:20 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	pthread_mutex_t *forks;
	int	i;
	
	forks = malloc(data->philosophers_len * sizeof(pthread_mutex_t));
	i = 0;
	while (i < data->philosophers_len)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	data->forks = forks;
	return (EXIT_SUCCESS);
}

int	destroy_forks(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->philosophers_len)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	data->forks = data->forks;
	return (EXIT_SUCCESS);
}

/**
 * INACTIVE
 */
// int assign_forks(t_data *data)
// {
// 	int	i;
// 	t_philosopher *philos;
	
// 	philos = data->philos;
// 	i = 0;
// 	while (i < data->philosophers_len)
// 	{
// 		philos[i].fork_right = philos[(i + 1) % data->philosophers_len].fork_left;
// 		printf("Left fork of philo %d is now also right fork of philo %d.\n", \
// 						(philos[i].id + 1) % data->philosophers_len, philos[i].id);
// 		i++;
// 	}
// 	return (EXIT_SUCCESS);
// }
