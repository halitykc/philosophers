/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:15:01 by hyakici           #+#    #+#             */
/*   Updated: 2025/08/07 14:56:12 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_rules	*rules;
	int		i;
	long	time_since_last_meal;

	philos = (t_philo *)arg;
	rules = philos[0].rules;
	while (1)
	{
		i = 0;
		while (i < rules->total_philos)
		{
			pthread_mutex_lock(&rules->meal_lock);
			time_since_last_meal = get_current_time() - philos[i].last_meal;
			pthread_mutex_unlock(&rules->meal_lock);
			if (time_since_last_meal > rules->time_to_die)
			{
				pthread_mutex_lock(&rules->dead_lock);
				if (!rules->is_dead)
				{
					rules->is_dead = 1;
					pthread_mutex_lock(&rules->write_lock);
					printf("%ld %d died\n", get_current_time()
						- rules->start_time, philos[i].philo_id);
					pthread_mutex_unlock(&rules->write_lock);
				}
				pthread_mutex_unlock(&rules->dead_lock);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
