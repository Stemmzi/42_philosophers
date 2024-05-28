/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:47:36 by sgeiger           #+#    #+#             */
/*   Updated: 2024/05/28 22:34:57 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_write(t_data *data, t_philo *philo, t_write_op op)
{
	pthread_mutex_lock(&data->lock);
	if (op == OP_FORK)
		printf("%ld %d has taken a fork\n", data->elapsed_time, philo->id);
	else if (op == OP_EAT)
		printf("%ld %d is eating\n", data->elapsed_time, philo->id);
	else if (op == OP_SLEEP)
		printf("%ld %d is sleeping\n", data->elapsed_time, philo->id);
	pthread_mutex_unlock(&data->lock);
}

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
	usleep(data->time_to_eat * 1000);
	philo->num_ate++;;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	safe_write(data, philo, OP_SLEEP);
	usleep(data->time_to_sleep * 1000);
	// data->dead = 1;
}

void	*dinner_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	// pthread_mutex_lock(&data->lock);
	// printf("Thread ID: %d\n", philo->id);
	// pthread_mutex_unlock(&data->lock);
	while (!data->dinner_ready)
		;
	while (!data->dead && data->full != data->num_of_philo)
	{
		sim_eat(data, philo);
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
		// usleep(150);
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

size_t	get_time(t_data *data)
{
	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	return ((s_time.tv_sec * 1000) + (s_time.tv_usec / 1000) - data->start_time);
}

int	main(int argc, char *argv[])
{
	t_data			data;
	struct timeval	start_time;

	ft_bzero(&data, sizeof(t_data));
	gettimeofday(&start_time, NULL);
	printf("Start  second: %ld\nStart msecond: %d\n", start_time.tv_sec, start_time.tv_usec);
	data.start_time = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
	input_handler(&data, argc, argv);
	init_data(&data);
	create_threads(&data);
	data.dinner_ready = true;
	while (!data.dead && data.full != data.num_of_philo)
	{
		data.elapsed_time = get_time(&data);
		usleep(100);
	}
	join_threads(&data);
	pthread_mutex_destroy(&data.lock);
	// gettimeofday(&start_time, NULL);
	// printf("End  second: %ld\nEnd msecond: %d\n", start_time.tv_sec, start_time.tv_usec);
	// printf("Time elapsed: %ld\n", (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000) - data.start_time);
}
