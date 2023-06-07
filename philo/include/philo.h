/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 09:27:31 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/07 12:22:55 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define NUM_PHILO "number_of_philosophers"
# define TIME_TO_DIE "time_to_die"
# define TIME_TO_EAT "time_to_eat"
# define TIME_TO_SLEEP "time_to_sleep"
# define MUST_EAT "[number_of_times_each_philosopher_must_eat]"

# define TOOK_FORK "%d %d has taken a fork\n"
# define EATING "%d %d is eating\n"
# define SLEEPING "%d %d is sleeping\n"
# define THINKING "%d %d is thinking\n"
# define DIED "%d %d died\n"

typedef struct s_tphilo
{
	int				id;
	int				ret;
	pthread_t		thread;
}					t_tphilo;

typedef struct s_philo
{
	int				count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	struct s_tphilo	**philosophers;
}					t_philo;

void	destroy_philosophers(t_philo *philo, int count);
int	alloc_philo(t_philo *philo);

void	print_usage(void);
void	debug_philo(t_philo *philo);

#endif