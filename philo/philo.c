/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:47:36 by sgeiger           #+#    #+#             */
/*   Updated: 2024/05/24 17:25:16 by sgeiger          ###   ########.fr       */
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

void	cleanup_exit(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	write(STDERR_FILENO, str, len);
	exit(EXIT_FAILURE);
}

void	input_checker(int argc, char *argv[])
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
}

void	create_threads(int argc, char *argv[])
{
	pthread_create();
}

int	main(int argc, char *argv[])
{
	input_checker(argc, argv);
	
	// create_threads();
	// join_threads();
	
}






// int	main(int argc, char *argv[])
// {
// 	pthread_t	thread;
// 	int			value;
// 	int			result;

// 	if (argc == 5)
// 	{
// 		printf("1, was here\n");
// 		value = 5;
// 		thread = (pthread_t)malloc(sizeof(pthread_t));
// 		pthread_create(&thread, NULL, (void *)init_thread, &value);
// 		printf("2, was here\n");
// 		result = pthread_join(thread, NULL);
// 		printf("3, was here\n");
// 	}
// 	else
// 	{
// 		printf("Error\n");
// 	}
// }