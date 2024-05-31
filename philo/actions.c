/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:34:43 by sgeiger           #+#    #+#             */
/*   Updated: 2024/05/31 02:31:22 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sim_eat_one(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	safe_write(data, philo, OP_FORK);
	while (!data->dinner_over)
		usleep(100);
	philo->status = SLEEPING;
	pthread_mutex_unlock(philo->r_fork);
}

void	sim_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	safe_write(data, philo, OP_FORK);
	pthread_mutex_lock(philo->l_fork);
	safe_write(data, philo, OP_FORK);
	if (philo->last_meal_time + data->time_to_die <= data->elapsed_time)
	{
		philo->status = DEAD;
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	else
	{
		safe_write(data, philo, OP_EAT);
		philo->last_meal_time = data->elapsed_time;
		sleep_until(data, data->time_to_eat);
		philo->num_ate++;
		if (philo->num_ate >= data->num_must_eat)
			data->full++;
		philo->status = SLEEPING;
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
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
		sleep_until(data, data->time_to_eat / 2);
	while (!data->dinner_over)
	{
		if (philo->status == EATING && data->num_of_philo == 1)
			sim_eat_one(data, philo);
		else if (philo->status == EATING)
			sim_eat(data, philo);
		if (philo->status == SLEEPING)
			sim_sleep(data, philo);
		if (philo->status == THINKING)
			sim_think(data, philo);
		if (philo->status == DEAD)
			return (NULL);
		// printf("test by thread %d\n", philo->id);
	}
	return (NULL);
}
