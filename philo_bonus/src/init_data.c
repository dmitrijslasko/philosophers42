/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 23:46:06 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/08 13:47:59 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	free_data(t_data *data)
{
	printf("PROCESS PID: %d\n", getpid());
	free(data->process_pids);
	sem_close(data->sem_forks);
	sem_close(data->sem_print);
	sem_unlink("/forks");
	sem_unlink("/print");
	//free(data->philo_threads);
	return (EXIT_SUCCESS);
}

/**
 * initialise program data (data struct)
 * @param data struct to hold the program's data
 * @param argc argument count
 * @param argv argument values
 * @return returns EXIT_SUCCESS on succesful exit
 */
int	init_data(t_data *data, int argc, char **argv)
{
	data->no_of_philos = int_atoi(argv[1]);
	data->time_to_die_ms = int_atoi(argv[2]);
	data->time_to_eat_ms = int_atoi(argv[3]);
	data->time_to_sleep_ms = int_atoi(argv[4]);
	data->no_of_meals_required = -1;
	if (argc == 6)
		data->no_of_meals_required = int_atoi(argv[5]);
	data->thread_start_delay_ms = data->time_to_eat_ms / THREAD_START_DELAY;
	data->simulation_start_time_ms = get_epoch_time_ms();
	data->simulation_start_time_us = get_epoch_time_us();
	data->simulation_status = 0;
	//data->forks = NULL;
	//data->philos = NULL;
	//data->philo_threads = NULL;
	//data->monitor_thread = (pthread_t) NULL;
	//data->data_access_mutex = safe_malloc(sizeof(t_mtx));
	//mutex_operation(data->data_access_mutex, INIT);
	//data->print_mutex = safe_malloc(sizeof(t_mtx));
	//mutex_operation(data->print_mutex, INIT);
	data->sem_forks = NULL;
	data->sem_data_access = NULL;
	data->sem_print = NULL;
	data->process_pids = NULL;
	return (EXIT_SUCCESS);
}
