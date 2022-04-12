/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 11:58:40 by jrossett          #+#    #+#             */
/*   Updated: 2022/04/12 15:53:50 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->dead == 0)
	{
		pthread_mutex_unlock(&philo->data->death);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death);
	return (1);
}

int	ft_nb_meal(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->data->eat);
	i = -1;
	if (philo->data->args.nb_eat == -17)
	{
		pthread_mutex_unlock(&philo->data->eat);
		return (0);
	}
	while (++i < philo->data->args.nb_philo)
	{
		if (philo->data->philo[i].nb_meal < philo->data->args.nb_eat)
		{
			pthread_mutex_unlock(&philo->data->eat);
			return (0);
		}
	}
	pthread_mutex_unlock(&philo->data->eat);
	return (1);
}

int	ft_check_dead(t_philo *philo, int nb_philo)
{
	int	i;

	if (ft_nb_meal(philo))
		return (1);
	pthread_mutex_lock(&philo->data->eat);
	i = -1;
	while (++i < nb_philo)
	{
		if ((g_t(&philo[i]) - philo[i].last_meal) > (unsigned int)philo[i].data->args.t_die)
		{
			pthread_mutex_unlock(&philo->data->eat);
			pthread_mutex_lock(&philo->data->death);
			philo[i].data->dead = 1;
			pthread_mutex_unlock(&philo->data->death);
			pthread_mutex_lock(&philo->data->print);
			printf("%u %d is died\n", g_t(&philo[i]), philo[i].index + 1);
			pthread_mutex_unlock(&philo->data->print);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->data->eat);
	return (0);
}

unsigned int	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

unsigned int	g_t(t_philo *philo)
{
	unsigned int	time;

	time = ft_time() - philo->data->day_t;
	return (time);
}