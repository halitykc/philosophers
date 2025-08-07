

#include "philo.h"

void	eat_philo(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_status("Has taken a fork", philo, philo->philo_id);
		pthread_mutex_lock(philo->l_fork);
		print_status("Has taken a fork", philo, philo->philo_id);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_status("Has taken a fork", philo, philo->philo_id);
		pthread_mutex_lock(philo->r_fork);
		print_status("Has taken a fork", philo, philo->philo_id);
	}
	pthread_mutex_lock(&philo->rules->meal_lock);
	print_status("Is eating", philo, philo->philo_id);
	philo->last_meal = get_current_time();
	ft_usleep(philo->rules->time_to_eat);
	philo->meal_eaten++;
	pthread_mutex_unlock(&philo->rules->meal_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleep_philo(t_philo *philo)
{
	print_status("Is sleeping", philo, philo->philo_id);
	ft_usleep(philo->rules->time_to_sleep);
}

void	think_philo(t_philo *philo)
{
	print_status("Is thinking", philo, philo->philo_id);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		pthread_mutex_lock(&philo->rules->dead_lock);
		if (philo->rules->is_dead)
		{
			pthread_mutex_unlock(&philo->rules->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->dead_lock);
		eat_philo(philo);
		sleep_philo(philo);
		think_philo(philo);
	}
	return (NULL);
}
