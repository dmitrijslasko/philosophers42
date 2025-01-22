/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:21:32 by dmlasko           #+#    #+#             */
/*   Updated: 2025/01/22 19:46:19 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void msleep(t_data *data, unsigned int sleep_time_ms) 
{
	(void)data;
    long long sleep_start_time_ms = get_epoch_time_ms();
    long long remaining_time;

    while ((remaining_time = sleep_time_ms - (get_epoch_time_ms() - sleep_start_time_ms)) > 0) 
    {
        if (data->simulation_is_on == 0)
            break ;
        if (remaining_time > 10)
            usleep(1000);
        else
            usleep(20);
    }
}
