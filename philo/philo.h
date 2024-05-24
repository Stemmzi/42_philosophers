/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:47:31 by sgeiger           #+#    #+#             */
/*   Updated: 2024/05/23 17:43:07 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_state	t_state;

typedef struct s_philo
{
	t_state		*state;
	pthread_t	th1;
	int			id;
	// int		time_to_die;
	// int		time_to_eat;
	// int		time_to_sleep;
	// int		num_must_eat;
}				t_philo;

struct s_state
{
	t_philo	*philos;
	int		num_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_must_eat;
};

#endif