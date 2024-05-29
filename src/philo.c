/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:47:36 by sgeiger           #+#    #+#             */
/*   Updated: 2024/05/29 18:40:10 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
--	Need difference between hard and soft cut.
	One fully the other one after the process.
--	Where checks for dead?
-- sometimes infinte loop, why?
*/
void	sim_eat(t_data *data, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		safe_write(data, philo, OP_FORK);
		pthread_mutex_lock(philo->r_fork);
		safe_write(data, philo, OP_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		safe_write(data, philo, OP_FORK);
		pthread_mutex_lock(philo->l_fork);
		safe_write(data, philo, OP_FORK);
	}
	safe_write(data, philo, OP_EAT);
	sleep_until(data, data->time_to_eat);
	philo->num_ate++;
	if (philo->num_ate == data->num_must_eat)
		data->full++;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->status = SLEEPING;
}

void	sim_sleep(t_data *data, t_philo *philo)
{
	safe_write(data, philo, OP_SLEEP);
	sleep_until(data, data->time_to_sleep);
	philo->status = THINKING;
}

void	sim_think(t_data *data, t_philo *philo)
{
	safe_write(data, philo, OP_THINK);
	philo->status = EATING;
}

void	*dinner_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (!data->dinner_ready)
		usleep(100);
	if (philo->id % 2 != 0)
		sleep_until(data, data->time_to_sleep / 2000);
	while (!data->dead && data->full != data->num_of_philo)
	{
		if (philo->status == EATING)
			sim_eat(data, philo);
		if (philo->status == SLEEPING)
			sim_sleep(data, philo);
		if (philo->status == THINKING)
			sim_think(data, philo);
	}
	return (NULL);
}

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_create(&data->philos[i].th, NULL, &dinner_routine, &data->philos[i]);
		i++;
	}
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join(data->philos[i].th, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data			data;
	struct timeval	start_time;

	ft_bzero(&data, sizeof(t_data));
	input_handler(&data, argc, argv);
	init_data(&data);
	create_threads(&data);
	gettimeofday(&start_time, NULL);
	data.start_time = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
	data.dinner_ready = true;
	while (!data.dead && data.full != data.num_of_philo)
	{
		data.elapsed_time = get_time(&data);
		usleep(100);
	}
	join_threads(&data);
	pthread_mutex_destroy(&data.lock);
}
