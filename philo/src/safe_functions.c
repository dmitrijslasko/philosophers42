/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:45:35 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/23 02:48:00 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(int size_bytes)
{
	void	*ptr;
	ptr = malloc(size_bytes);
	if (!ptr)
		print_error("Memory allocation failed!\n");
	return (ptr);
}
void	mutex_operation(p_mtx	*mutex, t_opcode opcode)
{
	if (opcode == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (opcode == DESTROY)
		pthread_mutex_destroy(mutex);
	else if (opcode == LOCK)
	{	
		if (pthread_mutex_trylock(mutex) == 0)
			pthread_mutex_unlock(mutex);
		else
			printf("Mutex already locked!\n");
	pthread_mutex_lock(mutex);
	}
	else if (opcode == UNLOCK)
		pthread_mutex_unlock(mutex);
	else
		print_error("Mutex operational code not recognized...\n");
}

void	fork_mutex_operation(p_mtx *fork, t_opcode opcode)
{
	if (opcode == INIT)
		pthread_mutex_init(fork, NULL);
	else if (opcode == DESTROY)
		pthread_mutex_destroy(fork);
	else if (opcode == LOCK)
	{
		pthread_mutex_lock(fork);
	}
	else if (opcode == UNLOCK)
	{
		pthread_mutex_unlock(fork);
	}
	else
		print_error("Mutex operational code not recognized...\n");
}