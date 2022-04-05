/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:13:24 by teambersaw        #+#    #+#             */
/*   Updated: 2022/04/05 15:50:54 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philosophers(void *philo)
{
	(void) philo;
	return (NULL);
}

pthread_mutex_t	*ft_init_fork(int nb_philo)
{
	pthread_mutex_t	*fork;
	int				i;

	i = -1;
	fork = malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (!fork)
		return (NULL);
	while (++i < nb_philo)
		if (pthread_mutex_init(&fork[i], NULL))
			return (free(fork), NULL);
	return (fork);
}

int	ft_init_philo(t_args args, t_philo *philo)
{
	pthread_t	*thread;

	thread = malloc(sizeof(pthread_t) * args.nb_philo);
	if (!thread)
		return (1);
	philo->thread = thread;
	philo->fork = ft_init_fork(args.nb_philo);
	if (!philo->fork)
		return (free(thread), 1);
	philo->args = args;
	if (pthread_mutex_init(&philo->sleep, NULL)
		|| pthread_mutex_init(&philo->eat, NULL)
		||pthread_mutex_init(&philo->think, NULL))
		return (1);
	return (0);
}

void	ft_free(t_philo philo)
{
	free(philo.thread);
	free(philo.fork);
}

int	ft_init_thread(t_args args)
{
	t_philo	philo;
	int		i;

	i = -1;
	if (ft_init_philo(args, &philo))
		return (1);
	while (++i < args.nb_philo)
		if (pthread_create(&philo.thread[i], NULL, &ft_philosophers, &philo))
			return (ft_free(philo), 1);
	i = -1;
	while (++i < args.nb_philo)
		if (pthread_join(philo.thread[i], NULL))
			return (ft_free(philo), 1);
	i = -1;
	while (++i < args.nb_philo)
		if (pthread_mutex_destroy(&philo.fork[i]))
			return (ft_free(philo), 1);
	if (pthread_mutex_destroy(&philo.eat)
		|| pthread_mutex_destroy(&philo.sleep)
		|| pthread_mutex_destroy(&philo.think))
	{
		free(philo.thread);
		free(philo.fork);
		return (1);
	}
	free(philo.thread);
	free(philo.fork);
	return (0);
}
