/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:25:00 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/27 09:25:02 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
returns the number of integers in n
*/
int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n = n * (-1);
	}
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

/*
returns the length of str
*/
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] != '\0')
			i++;
	}
	return (i);
}

/*
converts str to int representation and returns the converted int
only if it contains digits only; returns -1 on error
*/
int	philo_atoi(char *str)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '\0' && ft_intlen(num) == ft_strlen(str))
		return (num);
	return (-1);
}

/*
gets the current time and returns it to milliseconds
*/
size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*
modified version of usleep: calls usleep in 400 microsec increments
*/
void	ft_usleep(size_t time)
{
	size_t	begin;

	begin = get_time();
	while ((get_time() - begin) < time)
		usleep(400);
}
