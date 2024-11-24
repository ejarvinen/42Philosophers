/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:17:05 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/26 15:23:36 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
assigns forks to philosophers matching philosopher index to right fork; left
fork is in index - 1 except for the first philosopher; initializes a personal
meal lock to each philosopher
*/
static int	handout_forks(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->info.philos)
	{
		data->philo[index].r_fork = &data->forks[index];
		if (data->info.philos > 1)
		{
			if (index == 0)
				data->philo[index].l_fork = &data->forks[data->info.philos - 1];
			else
				data->philo[index].l_fork = &data->forks[index - 1];
		}
		data->philo[index].write_l = &data->write_l;
		data->philo[index].death_l = &data->death_l;
		if (pthread_mutex_init(&data->philo[index].meal_l, NULL) != 0)
			return (destroy_all(data, index, "Error initializing meal lock"));
		index++;
	}
	return (0);
}

/*
adds the remaining data to each philospher struct
*/
void	init_philo(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->info.philos)
	{
		data->philo[index].id = index + 1;
		data->philo[index].meals_had = 0;
		data->philo[index].info = &data->info;
		data->philo[index].death_flag = &data->death;
		index++;
	}
}

/*
initializes mutexes for each fork; initializes write and death locks
*/
int	init_locks(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->info.philos)
	{
		if (pthread_mutex_init(&data->forks[index], NULL) != 0)
			return (destroy_all(data, index, "Error initializing forks"));
		index++;
	}
	if (pthread_mutex_init(&data->write_l, NULL) != 0)
		return (destroy_all(data, index, "Error initializing write lock"));
	if (pthread_mutex_init(&data->death_l, NULL) != 0)
		return (destroy_all(data, index, "Error initializing death lock"));
	if (handout_forks(data) > 0)
		return (1);
	return (0);
}
