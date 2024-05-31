/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:01:18 by sgeiger           #+#    #+#             */
/*   Updated: 2024/05/31 17:16:04 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_unlock(&data->write_lock);
	pthread_mutex_destroy(&data->write_lock);
	while (i < data->num_of_philo)
	{
		pthread_mutex_unlock(&data->forks[i]);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

void	cleanup_threads(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->num_of_philo && data->philos[i].th)
	{
		if (pthread_join(data->philos[i].th, NULL) != 0)
			write(STDERR_FILENO, "Error: Failed to join threads\n", 30);
		i++;
	}
}

void	cleanup_exit(t_data *data, int exit_code)
{
	data->init_fail = true;
	cleanup_mutex(data);
	cleanup_threads(data);
	free(data->philos);
	free(data->forks);
	if (exit_code == 1)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

void	exit_str(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	write(STDERR_FILENO, str, len);
	exit(EXIT_FAILURE);
}
