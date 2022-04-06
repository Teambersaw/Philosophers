/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:13:24 by teambersaw        #+#    #+#             */
/*   Updated: 2022/04/06 16:06:36 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free(t_data data)
{
	free(data.fork);
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

int	ft_init_philo(t_args args, t_data *data)
{s
	pthread_t	*thr;

	data->fork = ft_init_fork(args.nb_philo);
	if (!data->fork)
		return (free(data), 1);
	data->args = args;
	if (pthread_mutex_init(&philo->sleep, NULL)
		|| pthread_mutex_init(&philo->eat, NULL)
		||pthread_mutex_init(&philo->think, NULL))
		return (ft_free(*philo), 1);
	return (0);
}

int	ft_init_thread(t_args args)
{
	t_data	data;
	int		i;

	i = -1;
	if (ft_init_philo(args, &data))
		return (1);
	while (++i < args.nb_philo)
		if (pthread_create(&data.philo.thread, NULL, &ph, &data))
			return (ft_free(data), 1);
	i = -1;
	while (++i < args.nb_philo)
		if (pthread_join(&data, NULL))
			return (ft_free(data), 1);
	i = -1;
	while (++i < args.nb_philo)
		if (pthread_mutex_destroy(&data.fork[i]))
			return (ft_free(data), 1);
	if (pthread_mutex_destroy(&data.eat)
		|| pthread_mutex_destroy(&data.sleep)
		|| pthread_mutex_destroy(&data.think))
		return (ft_free(data), 1);
	ft_free(data);
	return (0);
}
