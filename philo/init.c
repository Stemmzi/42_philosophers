/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 23:59:35 by sgeiger           #+#    #+#             */
/*   Updated: 2024/05/29 21:59:38 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->lock, NULL);
	data->forks = (t_mtx *)malloc(data->num_of_philo * sizeof(t_mtx));
	if (!data->forks)
		return ;
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philos = (t_philo *)malloc(data->num_of_philo * sizeof(t_philo));
	if (!data->philos)
		return ;
	while (i < data->num_of_philo)
	{
		data->philos[i].data = data;
		data->philos[i].num_ate = 0;
		data->philos[i].status = EATING;
		data->philos[i].id = i + 1;
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
	gettimeofday(&start_time, NULL);
	data->start_time = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
	while (i < data->num_of_philo)
	{
		data->philos[i].last_meal_time = data->start_time;
		i++;
	}
	data->elapsed_time = data->start_time;
}	
