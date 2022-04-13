/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:59:04 by jrossett          #+#    #+#             */
/*   Updated: 2022/04/13 17:05:25 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_printf(t_philo *philo, char c)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->stop == 0)
	{
		pthread_mutex_unlock(&philo->data->death);
		pthread_mutex_lock(&philo->data->print);
		if (c == 'f')
			printf("%u %d has taken a fork\n", g_t(philo), philo->index + 1);
		if (c == 'e')
			printf("%u %d is eating\n", g_t(philo), philo->index + 1);
		if (c == 's')
			printf("%u %d is sleeping\n", g_t(philo), philo->index + 1);
		if (c == 't')
			printf("%u %d is thinking\n", g_t(philo), philo->index + 1);
		pthread_mutex_unlock(&philo->data->print);
	}
	else
		pthread_mutex_unlock(&philo->data->death);
	return (0);
}

void	ft_key_lock(t_philo *philo)
{
	if (philo->index == philo->data->args.nb_philo - 1)
	{
		pthread_mutex_lock(&philo->data->fork[0]);
		ft_printf(philo, 'f');
		pthread_mutex_lock(&philo->data->fork[philo->index]);
		ft_printf(philo, 'f');
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork[philo->index]);
		ft_printf(philo, 'f');
		pthread_mutex_lock(&philo->data->fork[philo->index + 1]);
		ft_printf(philo, 'f');
	}
}

void	ft_key_unlock(t_philo *philo)
{
	if (philo->index == philo->data->args.nb_philo - 1)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->index]);
		pthread_mutex_unlock(&philo->data->fork[0]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->fork[philo->index + 1]);
		pthread_mutex_unlock(&philo->data->fork[philo->index]);
	}
}

int	ft_eat(t_philo *philo)
{
	ft_key_lock(philo);
	pthread_mutex_lock(&philo->data->eat);
	philo->last_meal = g_t(philo);
	pthread_mutex_unlock(&philo->data->eat);
	ft_printf(philo, 'e');
	ft_sleep(philo->data->args.t_eat);
	pthread_mutex_lock(&philo->data->eat);
	philo->nb_meal += 1;
	pthread_mutex_unlock(&philo->data->eat);
	ft_key_unlock(philo);
	return (0);
}

void	*philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	if (philo->index % 2)
		ft_sleep(philo->data->args.t_eat);
	if (philo->data->args.nb_eat == 0)
		return (NULL);
	while (1)
	{
		ft_eat(philo);
		ft_printf(philo, 's');
		ft_sleep(philo->data->args.t_sleep);
		ft_printf(philo, 't');
		pthread_mutex_lock(&philo->data->death);
		if (philo->data->stop == 1)
		{
			pthread_mutex_unlock(&philo->data->death);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->death);
	}
	return (NULL);
}
