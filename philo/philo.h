/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:47:31 by sgeiger           #+#    #+#             */
/*   Updated: 2024/05/29 22:04:12 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mtx;

typedef enum e_write_op
{
	OP_FORK,
	OP_EAT,
	OP_SLEEP,
	OP_THINK,
	OP_DIED
}	t_write_op;

//??
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
} t_status;

typedef struct s_philo
{
	t_data		*data;
	pthread_t	th;
	int			id;
	int			num_ate;
	long		last_meal_time;
	t_status	status;
	t_mtx		*l_fork;
	t_mtx		*r_fork;
}				t_philo;

struct s_data
{
	t_philo		*philos;
	t_mtx		*forks;
	int			full;
	long		start_time;
	long		elapsed_time;
	bool		dinner_ready;
	bool		dinner_over;
	int			num_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_must_eat;
	t_mtx		lock;
};

// utils
size_t	ft_strlen(const char *s);
void	ft_bzero(void *b, size_t len);
int		ft_atoi(const char *str);

long	get_time(t_data *data);
void	safe_write(t_data *data, t_philo *philo, t_write_op op);
void	sleep_until(t_data *data, long duration);

// input handler
void	input_handler(t_data *data, int argc, char *argv[]);

// init
void	init_mutex(t_data *data);
void	init_philo(t_data *data);
void	init_time(t_data *data);

//cleanup and exit
void	cleanup_exit(char *str);
void	join_threads(t_data *data);

#endif