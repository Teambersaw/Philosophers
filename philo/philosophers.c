/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:04:07 by teambersaw        #+#    #+#             */
/*   Updated: 2022/04/05 15:22:51 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
		return (i);
	}
	return (i);
}

int	ft_args_check(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '+' && ft_strlen(av[i]) == 1)
			return (1);
		if (ft_strlen(av[i]) > 11 || (ft_strlen(av[i]) == 11
				&& av[i][0] != '+'))
			return (1);
		j = -1;
		if (av[i][0] == '+')
			j++;
		while (av[i][++j])
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	unsigned int	res;
	int				i;
	int				j;

	i = -1;
	j = 0;
	res = 0;
	if (str[0] == '+')
		str++;
	while (str[++i])
		if (str[i] == '0')
			j++;
	if (j == ft_strlen(str))
		return (0);
	i = -1;
	while (str[++i])
		res = res * 10 + (str[i] - '0');
	if (res > 2147483647)
		return (-1);
	return ((int) res);
}

int	ft_init_args(t_args *args, int ac, char **av)
{
	args->nb_philo = ft_atoi(av[1]);
	args->t_die = ft_atoi(av[2]);
	args->t_eat = ft_atoi(av[3]);
	args->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		args->nb_eat = ft_atoi(av[5]);
	else
		args->nb_eat = -2;
	if (args->nb_eat == -1 || args->t_sleep == -1 || args->t_eat == -1
		|| args->t_die == -1 || args->nb_philo == -1)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_args	args;

	if ((ac != 5 && ac != 6) || ft_args_check(ac, av))
		return (printf("Wrong argument\n"), 1);
	if (ft_init_args(&args, ac, av))
		return (printf("Wrong argument\n"), 1);
	if (ac == 6 && args.nb_eat == 0)
		return (printf("All philosophers have eaten 0 times\n"), 0);
	if (av[1] == 0)
		return (printf("We need at least one philosopher"), 1);
	if (ft_init_thread(args))
		return (printf("Error\n"), 1);
	return (0);
}
