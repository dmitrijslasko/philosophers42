/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:49:02 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/13 22:21:06 by dmlasko          ###   ########.fr       */
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

typedef enum e_boolean
{
	FALSE,
	TRUE,
} 	t_boolean;

typedef struct s_fork
{
	int				fork_is_taken;
	pthread_mutex_t	fork;
}	t_fork;

typedef struct s_philosopher 
{
	int				id;
	int 			is_alive;
	long 			last_meal_time_ms;
	int				meals_count;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_data			*data;
}					t_philosopher;

typedef struct s_data 
{
	long long		simulation_start_time;
	int				simulation_is_on;
	int 			no_of_philosophers;
	int				time_to_die_ms;
	int 			time_to_eat_ms;
	int 			time_to_sleep_ms;
	int				no_of_meals_required;
	t_philosopher 	*philos;
	pthread_t 		*philo_threads;
	pthread_t 		monitor_thread;
	pthread_mutex_t	*forks;
 
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

// start_philo_threads.c
int	start_philo_threads(t_data *data);
int	join_philo_threads(t_data *data);

long	get_current_time_s(void);
long	get_current_time_ms(void);
long long get_current_time(void);
long long get_runtime(t_data *data);

int		start_monitor(t_data *data);
void	join_monitor_thread(t_data *data);

// init_forks.c
int	init_forks(t_data *data);
int	destroy_forks(t_data *data);

void	sleep_precisely(long milliseconds);
void	msleep(unsigned int sleep_time_ms);

int philo_is_alive(t_data *data, t_philosopher *philo);

#endif