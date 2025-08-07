/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:57:30 by hyakici           #+#    #+#             */
/*   Updated: 2025/08/07 14:22:06 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ERR_MSG1 "[WRONG USAGE]"
# define ERR_MSG2 "./philo <N> <time_to_die> <time_to_eat> <time_to_sleep>\n"
# define ERR_MSG3 "Every parametre must be positive\n"

typedef struct s_rules
{
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				total_philos;
	size_t			start_time;
	int				must_eat;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	int				is_dead;
	struct s_philo	*philos;

}					t_rules;

typedef struct s_philo
{
	pthread_t		thread;
	int				philo_id;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	size_t			last_meal;
	int				meal_eaten;
	t_rules			*rules;
}					t_philo;

size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);
int					ft_atoi(const char *nptr);
void				err_msg(void);
void				print_status(char *str, t_philo *philo, int id);

void				*philo_routine(void *arg);
void				*monitor_routine(void *arg);
int					start_threads(t_philo *philos, t_rules *rules);

#endif