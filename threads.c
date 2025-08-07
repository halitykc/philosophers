/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:17:38 by hyakici           #+#    #+#             */
/*   Updated: 2025/08/07 14:50:30 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_philo *philos, t_rules *rules)
{
	int			i;
	long		start_time;
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor_routine, philos) != 0)
	{
		printf("Failed to create monitor thread\n");
		return (1);
	}
	i = 0;
	while (i < rules->total_philos)
	{
		philos[i].last_meal = get_current_time();
		if (pthread_create(&philos[i].thread, NULL, philo_routine,
				&philos[i]) != 0)
		{
			printf("Failed to create philosopher thread %d\n", i);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < rules->total_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (0);
}
