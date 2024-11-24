/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:25:08 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/27 09:31:19 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> 
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_info
{
	int		philos;
	size_t	t_to_die;
	size_t	t_to_eat;
	size_t	t_to_sleep;
	int		meals;
	size_t	start;
}	t_info;

typedef struct s_philo
{
	pthread_t		t;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				id;
	int				meals_had;
	int				*death_flag;
	size_t			last_meal;
	t_info			*info;
	pthread_mutex_t	*write_l;
	pthread_mutex_t	*death_l;
	pthread_mutex_t	meal_l;
}	t_philo;

typedef struct s_data
{
	int				death;
	pthread_mutex_t	*forks;
	t_philo			*philo;
	t_info			info;
	pthread_mutex_t	write_l;
	pthread_mutex_t	death_l;
}	t_data;

/*				INITIALIZING				*/

void		init_philo(t_data *data);
int			init_locks(t_data *data);

/*				FOR ERROR					*/

int			ft_error(char *message);
int			free_error(t_data *data, char *message);
int			destroy_all(t_data *data, int mutexes, char *message);

/*				PHILO_UTILS					*/

int			ft_intlen(int n);
int			ft_strlen(char *str);
int			philo_atoi(char *str);
void		print_status(t_philo *philo, char *str);
void		ft_usleep(size_t time);
size_t		get_time(void);

/*				EATING, SLEEP AND REPEAT	*/

int			philo_routine(t_data *data);
int			did_someone_die(t_philo *philo,
				pthread_mutex_t *m1, pthread_mutex_t *m2);
int			eat(t_philo *philo);
int			daydream(t_philo *philo);
int			think(t_philo *philo);

/*				MONITORING					*/

void		monitor(t_data *data);

#endif
