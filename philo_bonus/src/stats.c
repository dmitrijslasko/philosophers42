/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:45:51 by dmlasko           #+#    #+#             */
/*   Updated: 2025/02/03 20:06:33 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_meal_count(t_data *data)
{
	int				i;
	t_philosopher	*philo;

	philo = data->philos;
	i = 0;
	mutex_operation(data->print_mutex, LOCK);
	while (i < data->no_of_philos)
	{
		printf(B_MAGENTA"Philosopher [%d]: %d\n"RST, \
					philo[i].id, philo[i].meals_count);
		i++;
	}
	mutex_operation(data->print_mutex, UNLOCK);
}

void	print_total_runtime(t_data *data)
{
	mutex_operation(data->print_mutex, LOCK);
	printf(YELLOW "TOTAL RUN TIME: %ld ms.\n" RST, get_sim_runtime_ms(data));
	mutex_operation(data->print_mutex, UNLOCK);
}

void	print_stats(t_data *data)
{
	print_meal_count(data);
	print_total_runtime(data);
}
