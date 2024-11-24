/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:24:25 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/27 09:24:27 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
unlocks and destroys all mutexes and frees program resources
*/
int	destroy_all(t_data *data, int mutexes, char *message)
{
	int	index;

	index = 0;
	while (index < mutexes)
	{
		pthread_mutex_destroy(&data->forks[index]);
		pthread_mutex_destroy(&data->philo[index].meal_l);
		index++;
	}
	pthread_mutex_destroy(&data->write_l);
	pthread_mutex_destroy(&data->death_l);
	return (free_error(data, message));
}

/*
frees all allocated program resources and prints message if specified
*/
int	free_error(t_data *data, char *message)
{	
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
	if (message)
		printf("Error: %s\n", message);
	return (1);
}

/*
prints error message and returns 1
*/
int	ft_error(char *message)
{
	printf("%s\n", message);
	return (1);
}
