/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 09:27:31 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/04 20:20:52 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft.h"
# include <errno.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define NUM_PHILO "number_of_philosophers"
# define TIME_TO_DIE "time_to_die"
# define TIME_TO_EAT "time_to_eat"
# define TIME_TO_SLEEP "time_to_sleep"
# define MUST_EAT "[number_of_times_each_philosopher_must_eat]"

# define TOOK_FORK "%lld %d has taken a fork\n"
# define EATING "%lld %d is eating\n"
# define SLEEPING "%lld %d is sleeping\n"
# define THINKING "%lld %d is thinking\n"
# define DIED "%lld %d died\n"

typedef struct timeval	t_timeval;
typedef struct s_sim	t_sim;

typedef bool			t_bool;

typedef struct s_philo
{
	int					id;
	int					ret;
	pthread_t			thread;
	long long			last_eat_at;
	int					dead;
	int					eaten_count;
	t_sim				*sim;
	pthread_mutex_t		lock;
}						t_philo;

struct					s_sim
{
	int					count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	t_bool				all_eaten;
	pthread_mutex_t		m_all_eaten;
	int					must_eat_count;
	pthread_mutex_t		m_eat_count;
	pthread_mutex_t		m_print;
	t_bool				end;
	pthread_mutex_t		m_end;
	long long			start_time;
	t_philo				*philosophers;
	pthread_mutex_t		*forks;
};

int						alloc_forks(t_sim *sim);
int						init_forks(t_sim *sim);
void					destroy_fork_mutex(pthread_mutex_t *forks, int count);

int						alloc_philosophers(t_sim *sim);
int						init_philosophers(t_sim *sim);

void					init_simulation(t_sim *philo);
void					destroy_simulation(t_sim *philo);
int						simulate(t_sim *sim);

void					print_usage(void);
void					sim_print(t_sim *sim, char *data, int id);
void					print_dead(t_sim *sim, char *data, int id);
void					ft_swap(int *a, int *b);
int						sim_end(t_sim *sim);

long long				time_to_ms(t_timeval time);
long long				time_now(void);
int						sleep_ms(long long ms);
long long				time_diff_ms(long long a, long long b);

void					*p_routine(void *data);
void					p_eat(t_sim *sim, t_philo *philo);
void					p_think(t_sim *sim, t_philo *philo);
void					p_sleep(t_sim *sim, t_philo *philo);

#endif