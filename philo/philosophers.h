/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:00:15 by teambersaw        #+#    #+#             */
/*   Updated: 2022/04/05 15:20:16 by jrossett         ###   ########.fr       */
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
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	t_args			args;
	pthread_mutex_t	eat;
	pthread_mutex_t	sleep;
	pthread_mutex_t	think;
}	t_philo;

int	ft_init_thread(t_args args);

#endif