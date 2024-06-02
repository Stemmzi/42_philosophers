/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:47:36 by sgeiger           #+#    #+#             */
/*   Updated: 2024/05/31 18:15:08 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_create(&data->philos[i].th, NULL,
				&dinner_routine, &data->philos[i]) != 0)
		{
			cleanup_exit(data, 1);
		}
		i++;
	}
}

void	philo_died(t_data *data, int i)
{
	pthread_mutex_lock(&data->philos[i].death_lock);
	if (!(data->philos[i].last_meal_time + data->time_to_die <= data->elapsed_time))
	{
		pthread_mutex_unlock(&data->philos[i].death_lock);
		return ;
	}
	pthread_mutex_lock(&data->write_lock);
	printf("%ld %d died\n", data->elapsed_time, data->philos[i].id);
	data->dinner_over = true;
	pthread_mutex_unlock(&data->write_lock);
	pthread_mutex_unlock(&data->philos[i].death_lock);
}

void	watch_threads(t_data *data)
{
	int	i;

	while (!data->dinner_over)
	{
		data->elapsed_time = get_time(data);
		i = 0;
		if (data->full >= data->num_of_philo)
		{
			data->dinner_over = true;
			break ;
		}
		while (i < data->num_of_philo)
		{
			if (!data->dinner_over && data->philos[i].last_meal_time
				+ data->time_to_die <= data->elapsed_time)
			{
				philo_died(data, i);
				break ;
			}
			i++;
		}
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	input_handler(&data, argc, argv);
	init_mutex(&data);
	init_philo(&data);
	create_threads(&data);
	init_time(&data);
	data.dinner_ready = true;
	watch_threads(&data);
	cleanup_exit(&data, 0);
}
