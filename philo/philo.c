/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:47:36 by sgeiger           #+#    #+#             */
/*   Updated: 2024/05/31 02:30:54 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
-- sometimes infinte loop, why?
-- now +1 allocated. right for left fork == NULL or not?
*/
void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_create(&data->philos[i].th, NULL,
			&dinner_routine, &data->philos[i]);
		i++;
	}
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
			// pthread_mutex_lock(&data->write_lock);
			// printf("dinner is over thread %d\n", data->philos[i].id);
			// pthread_mutex_unlock(&data->write_lock);
			break ;
		}
		while (i < data->num_of_philo)
		{
			if (!data->dinner_over && data->philos[i].last_meal_time + data->time_to_die <= data->elapsed_time)
			{
				pthread_mutex_lock(&data->write_lock);
				printf("%ld %d died\n", data->elapsed_time, data->philos[i].id);
				data->dinner_over = true;
				pthread_mutex_unlock(&data->write_lock);
				break;
			}
			i++;
		}
		// pthread_mutex_lock(&data->write_lock);
		// printf("\nALARM %d\n\n", data->full);
		// pthread_mutex_unlock(&data->write_lock);
		// usleep(100);
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
	cleanup_exit(&data);
}
