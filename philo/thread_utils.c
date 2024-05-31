/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 23:37:12 by sgeiger           #+#    #+#             */
/*   Updated: 2024/05/30 20:40:04 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_data *data)
{
	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	return ((s_time.tv_sec * 1000) + (s_time.tv_usec / 1000)
		- data->start_time);
}

void	safe_write(t_data *data, t_philo *philo, t_write_op op)
{
	pthread_mutex_lock(&data->write_lock);
	if (op == OP_FORK && !data->dinner_over)
		printf("%ld %d has taken a fork\n", data->elapsed_time, philo->id);
	else if (op == OP_EAT && !data->dinner_over)
		printf("%ld %d is eating\n", data->elapsed_time, philo->id);
	else if (op == OP_SLEEP && !data->dinner_over)
		printf("%ld %d is sleeping\n", data->elapsed_time, philo->id);
	else if (op == OP_THINK && !data->dinner_over)
		printf("%ld %d is thinking\n", data->elapsed_time, philo->id);
	pthread_mutex_unlock(&data->write_lock);
}

void	sleep_until(t_data *data, long duration)
{
	long	current_time;

	current_time = data->elapsed_time;
	while (!data->dinner_over && data->elapsed_time < (current_time + duration))
	{
		usleep(100);
	}
}
