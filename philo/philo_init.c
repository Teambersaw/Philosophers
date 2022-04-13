/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:13:24 by teambersaw        #+#    #+#             */
/*   Updated: 2022/04/13 15:58:22 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_one(t_args args)
{
	t_data	data;

	if (ft_init_data(args, &data))
		return (1);
	if (pthread_create(&data.philo[0].thread, NULL, &one, &data.philo[0]))
		return (free(data.fork), 1);
	if (pthread_join(data.philo[0].thread, NULL))
		return (free(data.fork), 1);
	if (pthread_mutex_destroy(&data.fork[0]))
		return (free(data.fork), 1);
	if (ft_destruct(&data))
		return (free(data.fork), 1);
	free(data.fork);
	free(data.philo);
	return (0);
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

void	ft_init_philo(t_philo *philo, int i, t_data *data)
{
	philo->index = i;
	philo->last_meal = 0;
	philo->data = data;
	philo->nb_meal = 0;
}

int	ft_init_data(t_args args, t_data *data)
{
	int	i;

	i = -1;
	data->day_t = ft_time();
	data->dead = 0;
	data->stop = 0;
	data->philo = malloc(sizeof(t_philo) * args.nb_philo);
	if (!data->philo)
		return (1);
	data->fork = ft_init_fork(args.nb_philo);
	if (!data->fork)
		return (1);
	data->args = args;
	while (++i < args.nb_philo)
		ft_init_philo(&data->philo[i], i, data);
	if (pthread_mutex_init(&data->death, NULL)
		|| pthread_mutex_init(&data->print, NULL)
		||pthread_mutex_init(&data->eat, NULL))
		return (free(data->fork), 1);
	return (0);
}

int	ft_init_thread(t_args args)
{
	t_data	data;
	int		i;

	i = -1;
	if (ft_init_data(args, &data))
		return (1);
	while (++i < args.nb_philo)
		if (pthread_create(&data.philo[i].thread, NULL, &philo, &data.philo[i]))
			return (free(data.fork), 1);
	while (1)
		if (ft_check_dead(data.philo, args.nb_philo))
			break ;
	i = -1;
	while (++i < args.nb_philo)
		if (pthread_join(data.philo[i].thread, NULL))
			return (free(data.fork), 1);
	i = -1;
	while (++i < args.nb_philo)
		if (pthread_mutex_destroy(&data.fork[i]))
			return (free(data.fork), 1);
	if (ft_destruct(&data))
		return (free(data.fork), 1);
	free(data.fork);
	free(data.philo);
	return (0);
}
