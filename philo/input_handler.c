/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 23:31:32 by sgeiger           #+#    #+#             */
/*   Updated: 2024/05/30 02:21:05 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size] != '\0')
		size++;
	return (size);
}

static int	ft_atoi(const char *str)
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

static int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	count;

	count = 0;
	while ((s1[count] != '\0' || s2[count] != '\0'))
	{
		if (s1[count] == s2[count])
			count++;
		else
			return ((unsigned char)s1[count] - (unsigned char)s2[count]);
	}
	return (-s2[count]);
}

bool	is_int(char *str)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	if (len > 10)
		return (false);
	i = 0;
	while (i < len)
	{
		if (str[i] >= 48 && str[i] <= 57)
			i++;
		else
			return (false);
	}
	if (len == 1 && str[0] == '0')
		return (false);
	if (len == 10 && ft_strcmp(str, "2147483647") > 0)
		return (false);
	return (true);
}

void	input_handler(t_data *data, int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		exit_str("Error: Input needs to have 4 or 5 arguments!\n");
	while (i < argc)
	{
		if (!is_int(argv[i]))
			exit_str("Error: Only integer > 0 as input allowed!\n");
		i++;
	}
	// data->full = 0;
	// data->dinner_ready = false;
	// data->dinner_over = false;
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_must_eat = ft_atoi(argv[5]);
	// else
	// 	data->num_must_eat = 0;
}
