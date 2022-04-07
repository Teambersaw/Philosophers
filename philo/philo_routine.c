/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:59:04 by jrossett          #+#    #+#             */
/*   Updated: 2022/04/07 15:20:30 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_printf(t_philo *philo, char c)
{
	pthread_mutex_lock(&philo->data->print);
	if (c == 'f')
		printf("%d %d has taken a fork\n", philo->data->args.nb_philo, philo->index);
	if (c == 'e')
		printf("%d %d is eating\n", philo->data->args.nb_philo, philo->index);
	if (c == 's')
		printf("%d %d is sleeping\n", philo->data->args.nb_philo, philo->index);
	if (c == 't')
		printf("%d %d is thinking\n", philo->data->args.nb_philo, philo->index);
	if (c == 'd')
		printf("%d %d is died\n", philo->data->args.nb_philo, philo->index);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	if (philo->index == philo->data->args.nb_philo)
	{
		pthread_mutex_lock(&philo->data->fork[philo->index]);
		ft_printf(philo, 'f');
		pthread_mutex_lock(&philo->data->fork[0]);
		ft_printf(philo, 'f');
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork[philo->index]);
		ft_printf(philo, 'f');
		pthread_mutex_lock(&philo->data->fork[philo->index + 1]);
		ft_printf(philo, 'f');
	}
	ft_printf(philo, 'e');
	usleep(philo->data->args.t_eat);
	if (philo->index == philo->data->args.nb_philo)
	{
		pthread_mutex_lock(&philo->data->fork[philo->index]);
		pthread_mutex_lock(&philo->data->fork[0]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->fork[philo->index]);
		pthread_mutex_unlock(&philo->data->fork[philo->index + 1]);
	}
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	ft_printf(philo, 's');
	usleep(philo->data->args.t_sleep);
	return (0);
}

int	ft_think(t_philo *philo)
{
	ft_printf(philo, 't');
	return (0);
}

void	*philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	while (1)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}
