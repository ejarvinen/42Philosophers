/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:49:01 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/27 09:31:06 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
checks if simulation should continue, otherwise prints the appropriate message
*/
int	think(t_philo *philo)
{
	if (did_someone_die(philo, NULL, NULL) > 0)
		return (1);
	print_status(philo, "is thinking");
	return (0);
}

/*
checks if simulation should continue, otherwise prints the appropriate message
and sleeps for the specified time to sleep
*/
int	daydream(t_philo *philo)
{
	if (did_someone_die(philo, NULL, NULL) > 0)
		return (1);
	print_status(philo, "is sleeping");
	ft_usleep(philo->info->t_to_sleep);
	return (0);
}

/*
locks two forks asigned to the philo struct, logs the meal time and updates
number of meals had, prints the appropriate message and sleeps for the
specified time to eat, unlocks forks and other mutexes accessed; returns 1
if simulation should stop, otherwise returns 0
*/
static int	right_fork_first(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (did_someone_die(philo, philo->r_fork, NULL) > 0)
		return (1);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	if (did_someone_die(philo, philo->l_fork, philo->r_fork) > 0)
		return (1);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_l);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_l);
	if (did_someone_die(philo, philo->l_fork, philo->r_fork) > 0)
		return (1);
	pthread_mutex_lock(&philo->meal_l);
	philo->meals_had++;
	print_status(philo, "is eating");
	pthread_mutex_unlock(&philo->meal_l);
	ft_usleep(philo->info->t_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

/*
locks two forks asigned to the philo struct, logs the meal time and updates
number of meals had, prints the appropriate message and sleeps for the
specified time to eat, unlocks forks and other mutexes accessed; returns 1
if simulation should stop, otherwise returns 0
*/
static int	left_fork_first(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (did_someone_die(philo, philo->l_fork, NULL) > 0)
		return (1);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	if (did_someone_die(philo, philo->r_fork, philo->l_fork) > 0)
		return (1);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_l);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_l);
	if (did_someone_die(philo, philo->l_fork, philo->r_fork) > 0)
		return (1);
	pthread_mutex_lock(&philo->meal_l);
	philo->meals_had++;
	print_status(philo, "is eating");
	pthread_mutex_unlock(&philo->meal_l);
	ft_usleep(philo->info->t_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (0);
}

/*
locks two forks asigned to the philo struct, logs the meal time and updates
number of meals had, prints the appropriate message and sleeps for the
specified time to eat, unlocks forks and other mutexes accessed; returns 1
if simulation should stop, otherwise returns 0
*/
int	eat(t_philo *philo)
{
	if (did_someone_die(philo, NULL, NULL) > 0)
		return (1);
	if (philo->id % 2 == 0)
		return (right_fork_first(philo));
	return (left_fork_first(philo));
}
