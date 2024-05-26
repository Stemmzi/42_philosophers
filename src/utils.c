/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 23:37:12 by sgeiger           #+#    #+#             */
/*   Updated: 2024/05/24 23:37:38 by sgeiger          ###   ########.fr       */
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
