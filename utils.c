/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:57:36 by hyakici           #+#    #+#             */
/*   Updated: 2025/08/07 14:43:46 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(10);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	s;

	res = 0;
	s = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			s = s * -1;
		i++;
	}
	while ((nptr[i] >= '0' && nptr[i] <= '9') && nptr[i])
		res = res * 10 + (nptr[i++] - '0');
	return (s * res);
}

void	err_msg(void)
{
	write(2, ERR_MSG1, 14);
	write(2, ERR_MSG2, 53);
	write(2, ERR_MSG3, 34);
}

void	print_status(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(&philo->rules->write_lock);
	time = get_current_time() - philo->rules->start_time;
	if (!philo->rules->is_dead)
	{
		printf("%zu %d %s\n", time, id, str);
	}
	pthread_mutex_unlock(&philo->rules->write_lock);
}
