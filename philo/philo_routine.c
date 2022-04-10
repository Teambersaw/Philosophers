/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:59:04 by jrossett          #+#    #+#             */
/*   Updated: 2022/04/09 15:46:44 by teambersaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

 unsigned int g_t(t_philo *philo)
{
	unsigned int	time;

	time = ft_time() - philo->data->day_t;
	return (time);
}

int	ft_printf(t_philo *philo, char c)
{
	pthread_mutex_lock(&philo->data->print);
	if (c == 'f')
		printf("%u %d has taken a fork\n", g_t(philo) , philo->index + 1);
	if (c == 'e')
		printf("%u %d is eating\n", g_t(philo) , philo->index + 1);
	if (c == 's')
		printf("%u %d is sleeping\n", g_t(philo) , philo->index + 1);
	if (c == 't')
		printf("%u %d is thinking\n", g_t(philo) , philo->index + 1);
	if (c == 'd')
		printf("%u %d is died\n", g_t(philo) , philo->index + 1);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}

void	ft_key_lock(t_philo *philo)
{
	if (philo->index == philo->data->args.nb_philo - 1)
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
		pthread_mutex_unlock(&philo->data->fork[philo->index]);
		pthread_mutex_unlock(&philo->data->fork[philo->index + 1]);
	}
}

int	ft_nb_meal(t_philo *philo)
{
	int	i;

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

int	ft_eat(t_philo *philo)
{
	ft_key_lock(philo);
	ft_printf(philo, 'e');
	usleep(philo->data->args.t_eat * 1000);
	pthread_mutex_lock(&philo->data->eat);
	philo->nb_meal += 1;
	philo->last_meal = g_t(philo);
	pthread_mutex_unlock(&philo->data->eat);
	ft_key_unlock(philo);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	ft_printf(philo, 's');
	usleep(philo->data->args.t_sleep * 1000);
	return (0);
}

int	ft_check_dead(t_philo *philo, int nb_philo)
{
	int	i;

	pthread_mutex_lock(&philo->data->sleep);
	while (1)
	{
		i = -1;
		while (++i < nb_philo)
		{
			printf("dernier repas du %de philo, %u\n", i, philo[i].last_meal);
			if ((g_t(&philo[i]) - philo[i].last_meal) > (unsigned int)philo[i].data->args.t_die)
			{
				ft_printf(&philo[i], 'd');
				philo[i].data->dead = 1;
				pthread_mutex_unlock(&philo->data->sleep);
				return (1);
			}
		}
	}
	pthread_mutex_unlock(&philo->data->sleep);
	return (0);
}

int oui = 7;

void	*philo(void *ptr)
{
	t_philo	*philo;
	philo = (t_philo *) ptr;
	if (philo->index % 2)
		usleep(philo->data->args.t_eat * 1000);
	while (1)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_printf(philo, 't');
	}
	return (NULL);
}