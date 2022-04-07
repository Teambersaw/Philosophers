/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:00:15 by teambersaw        #+#    #+#             */
/*   Updated: 2022/04/07 14:37:57 by jrossett         ###   ########.fr       */
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
	int				last_eat;
	int				index;
	int				t_eat;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t	*fork;
	t_philo			*philo;
	t_args			args;
	pthread_mutex_t	print;
	pthread_mutex_t	sleep;
	pthread_mutex_t	think;
}	t_data;

int		ft_init_thread(t_args args);
void	*philo(void *ptr);

#endif