/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 23:59:35 by sgeiger           #+#    #+#             */
/*   Updated: 2024/05/31 17:24:40 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		cleanup_exit(data, 1);
	data->forks = malloc(data->num_of_philo * sizeof(t_mtx));
	if (!data->forks)
		cleanup_exit(data, 1);
	memset(data->forks, 0, data->num_of_philo * sizeof(t_mtx));
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			cleanup_exit(data, 1);
		i++;
	}
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(data->num_of_philo * sizeof(t_philo));
	if (!data->philos)
		cleanup_exit(data, 1);
	memset(data->philos, 0, data->num_of_philo * sizeof(t_philo));
	while (i < data->num_of_philo)
	{
		data->philos[i].data = data;
		data->philos[i].num_ate = 0;
		data->philos[i].status = EATING;
		data->philos[i].id = i + 1;
		if (pthread_mutex_init(&data->philos[i].death_lock, NULL) != 0)
			cleanup_exit(data, 1);
		data->philos[i].r_fork = &data->forks[i];
		if (data->philos[i].id == data->num_of_philo)
			data->philos[i].l_fork = &data->forks[0];
		else
			data->philos[i].l_fork = &data->forks[i + 1];
		i++;
	}
}

void	init_time(t_data *data)
{
	struct timeval	start_time;
	int				i;

	i = 0;
	if (gettimeofday(&start_time, NULL) != 0)
		cleanup_exit(data, 1);
	data->start_time = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
	while (i < data->num_of_philo)
	{
		data->philos[i].last_meal_time = 0;
		i++;
	}
}
