/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:51:12 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/26 15:10:27 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
performs the following operations in write lock: obtains a time stamp, 
checks if simulation should end; if not, prints the given string
*/
void	print_status(t_philo *philo, char *str)
{	
	size_t	timestamp;

	pthread_mutex_lock(philo->write_l);
	timestamp = get_time() - philo->info->start;
	if (did_someone_die(philo, philo->write_l, NULL) > 0)
		return ;
	printf("%zu %d %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(philo->write_l);
}
