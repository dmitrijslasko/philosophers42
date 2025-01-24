/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 00:17:25 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/24 00:14:51 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(data->no_of_philosophers * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (MALLOC_FAIL);
	i = 0;
	while (i < data->no_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		if (DEBUG)
			printf(YELLOW"Fork %d initialized\n"RESET, i + 1);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_of_philosophers)
		pthread_mutex_destroy(&data->forks[i++]);
	if (DEBUG)
		printf(B_MAGENTA">>>>>>>>>>>>> Forks destroyed\n"RESET);
	return (EXIT_SUCCESS);
}
