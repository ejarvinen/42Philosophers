/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 06:42:40 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/26 15:25:14 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
checks for validity of the input parameters and saves them to data struct
*/
static int	validate_input(int argc, char **argv, t_data *data)
{
	if (philo_atoi(argv[1]) < 1)
		return (ft_error("Invalid number of philosophers"));
	data->info.philos = philo_atoi(argv[1]);
	if (philo_atoi(argv[2]) < 1)
		return (ft_error("Invalid time to die"));
	data->info.t_to_die = philo_atoi(argv[2]);
	if (philo_atoi(argv[3]) < 1)
		return (ft_error("Invalid time to eat"));
	data->info.t_to_eat = philo_atoi(argv[3]);
	if (philo_atoi(argv[4]) < 1)
		return (ft_error("Invalid time to sleep"));
	data->info.t_to_sleep = philo_atoi(argv[4]);
	if (argc == 6)
	{
		if (philo_atoi(argv[5]) < 1)
			return (ft_error("Invalid number of meals"));
		data->info.meals = philo_atoi(argv[5]);
	}
	else
		data->info.meals = -1;
	return (0);
}

/*
verifies input, mallocs data structures, initializes mutexes,
sets simulation start specs, runs philosopher routine and cleans up
resources
*/
int	main(int argc, char **argv)
{
	t_data			data;
	int				ret;

	if (argc < 5 || argc > 6)
		return (ft_error("Invalid number of arguments"));
	if (validate_input(argc, argv, &data) > 0)
		return (1);
	data.philo = malloc(sizeof(t_philo) * data.info.philos);
	if (!data.philo)
		return (ft_error("allocating philo failed"));
	data.forks = malloc(sizeof(pthread_mutex_t) * data.info.philos);
	if (!data.forks)
		return (free_error(&data, "fork malloc fail"));
	if (init_locks(&data) > 0)
		return (1);
	init_philo(&data);
	data.info.start = get_time();
	data.death = 0;
	ret = philo_routine(&data);
	destroy_all(&data, data.info.philos, NULL);
	return (ret);
}
