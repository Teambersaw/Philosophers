/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:00:15 by teambersaw        #+#    #+#             */
/*   Updated: 2022/04/11 17:07:16 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	int	nb_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	nb_eat;
}	t_args;

typedef struct s_philo
{
	pthread_t		thread;
	int				last_meal;
	int				index;
	int				nb_meal;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	unsigned int	dead;
	pthread_mutex_t	*fork;
	t_philo			*philo;
	t_args			args;
	unsigned int	day_t;
	pthread_mutex_t	print;
	pthread_mutex_t	sleep;
	pthread_mutex_t	eat;
	pthread_mutex_t	manger;
}	t_data;

int				ft_init_thread(t_args args);
void			*philo(void *ptr);
int				ft_check_dead(t_philo *philo, int nb_philo);
unsigned int	ft_time(void);
int				ft_nb_meal(t_philo *philo);

#endif