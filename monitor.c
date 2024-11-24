/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 08:46:42 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/27 12:05:27 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
if meals is given, checks if all philosophers have eaten the specified
number of meals; if so, updates death flag and returns 1; returns 0 if
simulation can continue
*/
static int	all_fed(t_data *data)
{
	int	fed_philos;
	int	index;
	int	tot_meals;

	if (data->info.meals == -1)
		return (0);
	fed_philos = 0;
	index = 0;
	while (index < data->info.philos)
	{
		pthread_mutex_lock(&data->philo[index].meal_l);
		tot_meals = data->philo[index].meals_had;
		pthread_mutex_unlock(&data->philo[index].meal_l);
		if (tot_meals >= data->info.meals)
			fed_philos++;
		index++;
	}
	if (fed_philos == data->info.philos)
	{
		pthread_mutex_lock(&data->death_l);
		data->death = 1;
		pthread_mutex_unlock(&data->death_l);
		return (1);
	}
	return (0);
}

/*
loops through all philosophers and compares the current time
to their last meal, if more time has elapsed than the time to die,
death flag is updated and 1 is returned; returns 0 if simulation can
continue
*/
static int	check_for_deaths(t_data *data)
{
	int		index;

	index = 0;
	while (index < data->info.philos)
	{
		pthread_mutex_lock(&data->philo[index].meal_l);
		if ((get_time() - data->philo[index].last_meal) > data->info.t_to_die)
		{
			pthread_mutex_unlock(&data->philo[index].meal_l);
			print_status(&data->philo[index], "died");
			pthread_mutex_lock(&data->death_l);
			data->death = 1;
			pthread_mutex_unlock(&data->death_l);
			return (1);
		}
		pthread_mutex_unlock(&data->philo[index].meal_l);
		index++;
	}
	return (0);
}

/*
waits before entering a loop to check if any of the philosophers
has died or if all of them have eaten the specified number of meals
*/
void	monitor(t_data *data)
{
	ft_usleep(42);
	while (1)
	{
		if (check_for_deaths(data) != 0)
			return ;
		if (all_fed(data) != 0)
			return ;
	}
}
