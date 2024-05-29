/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 23:37:12 by sgeiger           #+#    #+#             */
/*   Updated: 2024/05/29 01:57:34 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size] != '\0')
		size++;
	return (size);
}

void	ft_bzero(void *b, size_t len)
{
	unsigned char	*ptr;

	ptr = b;
	while (len > 0)
	{
		*ptr = 0;
		ptr++;
		len--;
	}
}

int	ft_atoi(const char *str)
{
	int	count;
	int	minus;
	int	result;
	int	count2;

	count = 0;
	result = 0;
	minus = 1;
	count2 = 0;
	while (str[count] == ' ' || str[count] == '\t' || str[count] == '\n'
		|| str[count] == '\v' || str[count] == '\f' || str[count] == '\r')
		count++;
	while ((str[count] == '-' || str[count] == '+') && count2 != 1)
	{
		if (str[count] == '-')
			minus = minus * -1;
		count++;
		count2++;
	}
	while (str[count] >= 48 && str[count] <= 57)
	{
		result = result * 10 + (str[count] - 48);
		count++;
	}
	return (result * minus);
}

long	get_time(t_data *data)
{
	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	return ((s_time.tv_sec * 1000) + (s_time.tv_usec / 1000) - data->start_time);
}

void	safe_write(t_data *data, t_philo *philo, t_write_op op)
{
	pthread_mutex_lock(&data->lock);
	if (op == OP_FORK)
		printf("%ld %d has taken a fork\n", data->elapsed_time, philo->id);
	else if (op == OP_EAT)
		printf("%ld %d is eating\n", data->elapsed_time, philo->id);
	else if (op == OP_SLEEP)
		printf("%ld %d is sleeping\n", data->elapsed_time, philo->id);
	else if (op == OP_THINK)
		printf("%ld %d is thinking\n", data->elapsed_time, philo->id);
	pthread_mutex_unlock(&data->lock);
}

void	sleep_until(t_data *data, long duration)
{
	long	current_time;

	current_time = data->elapsed_time;
	while(!data->dead && data->elapsed_time < (current_time + duration))
	{
		usleep(100);
	}
}
