/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 08:45:30 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/27 11:38:25 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
checks for the death_flag and unlocks mutexes if specified
*/
int	did_someone_die(t_philo *philo, pthread_mutex_t *m1, pthread_mutex_t *m2)
{
	pthread_mutex_lock(philo->death_l);
	if (*(philo->death_flag) > 0)
	{
		pthread_mutex_unlock(philo->death_l);
		if (m1)
			pthread_mutex_unlock(m1);
		if (m2)
			pthread_mutex_unlock(m2);
		return (1);
	}
	pthread_mutex_unlock(philo->death_l);
	return (0);
}

/*
sets the start time for each thread in last_meal, checks for the number of
philosophers and enters the action loop of eat, sleep, think if enough
philosophers is given
*/
static void	*loop(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	pthread_mutex_lock(&philo->meal_l);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_l);
	if (philo->info->philos == 1)
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
		ft_usleep(philo->info->t_to_die + 1);
		if (did_someone_die(philo, philo->r_fork, NULL) > 0)
			return (phil);
	}
	while (!did_someone_die(philo, NULL, NULL))
	{
		if (eat(philo) == 1)
			return (phil);
		if (daydream(philo) == 1)
			return (phil);
		if (think(philo) == 1)
			return (phil);
	}
	return (phil);
}

/*
joins threads according to given index
*/
static void	kill_philos(t_data *data, int index)
{
	while (index > 0)
	{
		index--;
		pthread_join(data->philo[index].t, NULL);
	}
}

/*
initiates threads, runs monitor script and joins threads in case of
an error / simulation ends
*/
int	philo_routine(t_data *data)
{
	int			index;

	index = 0;
	while (index < data->info.philos)
	{
		if (pthread_create(&data->philo[index].t, NULL,
				&loop, &data->philo[index]) != 0)
		{
			pthread_mutex_lock(&data->death_l);
			data->death = 1;
			pthread_mutex_unlock(&data->death_l);
			kill_philos(data, index);
			return (1);
		}
		index++;
	}
	monitor(data);
	kill_philos(data, data->info.philos);
	return (0);
}
