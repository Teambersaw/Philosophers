/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 11:58:40 by jrossett          #+#    #+#             */
/*   Updated: 2022/05/03 15:08:44 by teambersaw       ###   ########.fr       */
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

	if (philo->data->args.nb_eat == -17)
		return (0);
	pthread_mutex_lock(&philo->data->eat);
	i = -1;
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

void	ft_dead_check(t_philo *philo, int i)
{
	pthread_mutex_unlock(&philo->data->eat);
	pthread_mutex_lock(&philo->data->death);
	philo[i].data->dead = 1;
	philo->data->stop = 1;
	pthread_mutex_unlock(&philo->data->death);
}

int	ft_check_dead(t_philo *philo, int nb_philo)
{
	int	i;
	usleep(100);
	if (ft_nb_meal(philo))
	{
		pthread_mutex_lock(&philo->data->death);
		philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	pthread_mutex_lock(&philo->data->eat);
	i = -1;
	while (++i < nb_philo)
	{
		if ((g_t(&philo[i]) - philo[i].last_meal)
			> (unsigned int)philo[i].data->args.t_die)
		{
			ft_dead_check(philo, i);
			pthread_mutex_lock(&philo->data->print);
			printf("%u %d is died\n", g_t(&philo[i]), philo[i].index + 1);
			pthread_mutex_unlock(&philo->data->print);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->data->eat);
	return (0);
}

void	*one(void	*ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	if (philo->data->args.nb_eat == 0)
		return (NULL);
	pthread_mutex_lock(&philo->data->fork[0]);
	printf("%u 1 has taken a fork\n", g_t(philo));
	ft_sleep(philo->data->args.t_die);
	pthread_mutex_unlock(&philo->data->fork[0]);
	printf("%u is died\n", g_t(&philo[0]));
	return (NULL);
}
