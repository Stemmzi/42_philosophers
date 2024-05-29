/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 23:31:32 by sgeiger           #+#    #+#             */
/*   Updated: 2024/05/29 22:02:23 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_number(char *str)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		if (str[i] >= 48 && str[i] <= 57)
			i++;
		else
			return (false);
	}
	return (true);
}

void	input_handler(t_data *data, int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		cleanup_exit("Error: Input needs to have 4 or 5 arguments!\n");
	while (i < argc)
	{
		if (!is_number(argv[i]))
			cleanup_exit("Error: Only positive numbers as input!\n");
		i++;
	}
	data->full = 0;
	data->dinner_ready = false;
	data->dinner_over = false;
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_must_eat = ft_atoi(argv[5]);
	else
		data->num_must_eat = 0;
	// check_numbers(); for min/max
}
