/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:59:04 by jrossett          #+#    #+#             */
/*   Updated: 2022/05/03 15:08:07 by teambersaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_printf(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->stop != 0 || philo->data->dead != 0)
	{
		pthread_mutex_unlock(&philo->data->death);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death);
	pthread_mutex_lock(&philo->data->print);
	printf("%u %d %s\n", g_t(philo), philo->index + 1, str);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}

void	ft_key_lock(t_philo *philo)
{
	if (philo->index == philo->data->args.nb_philo - 1)
	{
		pthread_mutex_lock(&philo->data->fork[0]);
		pthread_mutex_lock(&philo->data->eat);
		ft_printf(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->data->eat);
		pthread_mutex_lock(&philo->data->fork[philo->index]);
		pthread_mutex_lock(&philo->data->eat);
		ft_printf(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->data->eat);
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork[philo->index]);
		pthread_mutex_lock(&philo->data->eat);
		ft_printf(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->data->eat);
		pthread_mutex_lock(&philo->data->fork[philo->index + 1]);
		pthread_mutex_lock(&philo->data->eat);
		ft_printf(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->data->eat);
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
	ft_printf(philo, "is eating");
	pthread_mutex_unlock(&philo->data->eat);
	ft_sleep(philo->data->args.t_eat);
	pthread_mutex_lock(&philo->data->eat);
	philo->nb_meal += 1;
	pthread_mutex_unlock(&philo->data->eat);
	ft_key_unlock(philo);
	return (0);
}


void	ft_think(t_philo *philo)
{
	int i;

	i = ((philo->data->args.t_die - (philo->data->args.t_eat \
			+ philo->data->args.t_sleep)) / 2);
	if (i > 0)
		usleep(i * 1000);
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
		pthread_mutex_lock(&philo->data->eat);
		ft_printf(philo, "is sleeping");
		pthread_mutex_unlock(&philo->data->eat);
		ft_sleep(philo->data->args.t_sleep);
		pthread_mutex_lock(&philo->data->eat);
		ft_printf(philo, "is thinking");
		pthread_mutex_unlock(&philo->data->eat);
		pthread_mutex_lock(&philo->data->death);
		if (philo->data->stop == 1)
			return (pthread_mutex_unlock(&philo->data->death), NULL);
		pthread_mutex_unlock(&philo->data->death);
		ft_think(philo);
	}
	return (NULL);
}
