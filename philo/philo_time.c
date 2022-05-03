/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:46:24 by jrossett          #+#    #+#             */
/*   Updated: 2022/04/27 23:00:39 by teambersaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	ft_sleep(unsigned int sleep)
{
	int	time;

	time = ft_time();
	while ((ft_time() - time) < sleep)
		usleep(50);
}

int	ft_destruct(t_data *data)
{
	if (pthread_mutex_destroy(&data->print)
		|| pthread_mutex_destroy(&data->eat)
		|| pthread_mutex_destroy(&data->death))
		return (1);
	return (0);
}
