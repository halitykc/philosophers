/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:57:33 by hyakici           #+#    #+#             */
/*   Updated: 2025/08/07 13:49:34 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	init_mutex(pthread_mutex_t *fork, t_rules *rules)
{
	int	i;

	pthread_mutex_init(&rules->write_lock, NULL);
	pthread_mutex_init(&rules->dead_lock, NULL);
	pthread_mutex_init(&rules->meal_lock, NULL);
	i = -1;
	while (++i < rules->total_philos)
	{
		pthread_mutex_init(&fork[i], NULL);
	}
}

void	init_data(t_rules *rule, t_philo *philos, char **argv,
		pthread_mutex_t *fork)
{
	int	i;

	rule->total_philos = ft_atoi(argv[1]);
	rule->time_to_die = ft_atoi(argv[2]);
	rule->time_to_eat = ft_atoi(argv[3]);
	rule->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		rule->must_eat = ft_atoi(argv[5]);
	else
		rule->must_eat = -1;
	rule->is_dead = 0;
	rule->start_time = get_current_time();
	rule->philos = philos;
	i = -1;
	while (++i < rule->total_philos)
	{
		philos[i].philo_id = i + 1;
		philos[i].meal_eaten = 0;
		philos[i].rules = rule;
		philos[i].last_meal = get_current_time();
		philos[i].l_fork = &fork[i];
		philos[i].r_fork = &fork[(i + 1) % rule->total_philos];
	}
}

int	main(int argc, char *argv[])
{
	pthread_mutex_t	fork[200];
	t_philo			philos[200];
	t_rules			rules;
	int				i;

	if ((argc == 6 || argc == 5) && check_args(argv))
	{
		init_data(&rules, philos, argv, fork);
		init_mutex(fork, &rules);
		start_threads(philos, &rules);
	}
	else
		err_msg();
	return (0);
}
