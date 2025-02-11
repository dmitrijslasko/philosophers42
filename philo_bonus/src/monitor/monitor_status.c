#include "philo_bonus.h"

void	*monitor_philo_status(void *args)
{
	t_data *data;
	int i;

	data = (t_data *)args;
	i = data->philo_index;
	while (data->philos[i].is_alive && data->philos[i].is_full == 0)
	{
		data->philos[i].is_alive = philo_is_alive(data, &data->philos[i]);
		data->philos[i].is_full = philo_is_full(data, &data->philos[i]);
		usleep(10);
	}
	if (data->philos[i].is_alive == 0)
		write_status(data, &data->philos[i], DIED);
	data->simulation_is_on = 0;
	return (NULL);
}
