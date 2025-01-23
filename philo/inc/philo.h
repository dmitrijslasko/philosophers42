/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:49:02 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/23 21:36:54 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

// LIBRARIES
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

# include "settings.h"

// STRUCTS
typedef struct s_data t_data;
typedef pthread_mutex_t p_mtx;

typedef enum e_boolean
{
	FALSE,
	TRUE,
} 	t_boolean;

typedef	enum e_opcode
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
}	t_opcode;

typedef	enum e_status
{
	TAKEN_LEFT_FORK,
	TAKEN_RIGHT_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_status;

typedef struct s_philosopher
{
	int				id;
	int				is_full;
	long 			last_meal_time_ms;
	int				meals_count;
	p_mtx			*fork_left;
	p_mtx			*fork_right;
	t_data			*data;
}					t_philosopher;

typedef struct s_data
{
	int 			no_of_philosophers;
	int				time_to_die_ms;
	int 			time_to_eat_ms;
	int 			time_to_sleep_ms;
	int				no_of_meals_required;
	int				no_of_meals_min;
	int				thread_start_delay_ms;
	long long		simulation_start_time_ms;
	long long		simulation_start_time_us;
	long long		simulation_runtime_ms;
	int				simulation_is_on;
	int				all_threads_created;
	p_mtx			*forks;
	t_philosopher 	*philos;
	pthread_t 		*philo_threads;
	pthread_t 		monitor_thread;
	p_mtx			data_access_mutex;
	p_mtx			no_of_meals_min_mutex;
}					t_data;

// FUNCTIONS
// parsing.c
int contains_only_digits(const char *str);
int is_valid_single_argument(const char *str);
int is_valid_input(char **argv, int argc);

// aux.c
int int_atoi(const char *str);
int	ft_strlen(const char *str);

// data.c
int	init_data(t_data *data, int argc, char **argv);

// init_philos.c
int init_philos(t_data *data);

int assign_forks(t_data *data);

// create_philo_threads.c
int	create_philo_threads(t_data *data);
int	join_philo_threads(t_data *data);

long	get_epoch_time_s_part(void);
long	get_epoch_time_us_part(void);
long long get_epoch_time_ms(void);
long long get_epoch_time_us(void);
long long get_simulation_runtime_ms(t_data *data);
long long get_simulation_runtime_us(t_data *data);

int		create_monitor(t_data *data);
void	join_monitor_thread(t_data *data);

// init_forks.c
int	init_forks(t_data *data);
int	destroy_forks(t_data *data);

void	sleep_precisely(long milliseconds);
void	msleep(t_data *data, unsigned int sleep_time_ms);

int philo_is_alive(t_data *data, t_philosopher *philo);

void	print_error(char *str);

void	*safe_malloc(int size_bytes);
void	mutex_operation(p_mtx	*mutex, t_opcode opcode);

void 	wait_for_all_threads(t_data *data);

void	fork_mutex_operation(p_mtx *fork, t_opcode opcode);

void	write_status(t_data *data, t_philosopher *philo, t_status status);
void	write_status_debug(t_data *data, t_philosopher *philo, t_status status);


// stats.c
void    print_meal_count(t_data *data);
void print_stats(t_data *data);

#endif
