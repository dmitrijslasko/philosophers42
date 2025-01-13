/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 00:17:25 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/13 22:13:21 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	pthread_mutex_t *forks;
	int	i;
	
	forks = malloc(data->no_of_philosophers * sizeof(pthread_mutex_t));
	i = 0;
	while (i < data->no_of_philosophers)
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
	while (i < data->no_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	data->forks = data->forks;
	return (EXIT_SUCCESS);
}
