/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:13:24 by teambersaw        #+#    #+#             */
/*   Updated: 2022/04/04 16:16:08 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philosophers(void *philo)
{
	return (NULL);
}

int	ft_philo_init(t_args args, t_philo *philo)
{
	int			i;
	pthread_t	*thread;

	thread = malloc(sizeof(pthread_t) * args.nb_philo);
	if (!thread)
		return (-1);
	philo->thread = thread;
	return (0);
}

int	init_thread(t_args args)
{
	t_philo	philo;
	int		i;

	i = -1;
	ft_philo_init(args, &philo);
	while (++i < args.nb_philo)
	{
		if (pthread_create(&philo.thread[i], NULL, &ft_philosophers, &philo))
			return (1);
	}
	i = -1;
	while (++i < args.nb_philo)
	{
		if (pthread_join(philo.thread[i], NULL))
			return (1);
	}
	return (0);
}
