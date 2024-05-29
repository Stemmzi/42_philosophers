/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:01:18 by sgeiger           #+#    #+#             */
/*   Updated: 2024/05/29 22:02:18 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	cleanup_exit(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	write(STDERR_FILENO, str, len);
	// free(data->philos);
	exit(EXIT_FAILURE);
}
