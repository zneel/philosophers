/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 09:27:31 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/08 13:18:53 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
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

# define TOOK_FORK "%lld %d has taken a fork\n"
# define EATING "%lld %d is eating\n"
# define SLEEPING "%lld %d is sleeping\n"
# define THINKING "%lld %d is thinking\n"
# define DIED "%lld %d died\n"

typedef struct timeval	t_timeval;

enum					e_state
{
	EAT,
	SLEEP,
	THINK,
	DEAD,
};

typedef struct s_tphilo
{
	int					id;
	int					ret;
	pthread_t			thread;
	long long			last_eat_at;
	int					dead;
	int					eaten_count;
	enum e_state		state;
}						t_tphilo;

typedef struct s_sim
{
	int					count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
	pthread_mutex_t		sim;
	int					end;
	long long			start_time;
	struct s_tphilo		**philosophers;
	pthread_mutex_t		**forks;
}						t_sim;

typedef struct s_args
{
	struct s_tphilo		*philo;
	struct s_sim		*sim;
}						t_args;

void					destroy_forks(pthread_mutex_t **forks, int count);
int						alloc_forks(t_sim *sim);
int						pick_up_release_forks(t_sim *sim, t_tphilo *philo);
int						init_forks(t_sim *sim);
void					destroy_fork_mutex(pthread_mutex_t **forks, int count);

void					destroy_philosophers(t_tphilo **philos, int count);
int						alloc_philosophers(t_sim *sim);
int						init_philosophers(t_sim *sim);
int						is_dead(t_sim *sim, t_tphilo *philo);

void					init_simulation(t_sim *philo);
void					exit_simulation(t_sim *philo);
int						simulate(t_sim *sim);

void					print_usage(void);
void					debug_sim(t_sim *sim);

long long				time_to_ms(t_timeval time);
long long				time_now(void);
int						sleep_ms(long long ms);
long long				time_diff_ms(long long a, long long b);

void					*p_routine(void *philo);
int						p_dead(t_sim *sim, t_tphilo *philo);
void					p_eat(t_sim *sim, t_tphilo *philo);
void					p_think(t_sim *sim, t_tphilo *philo);
void					p_sleep(t_sim *sim, t_tphilo *philo);

#endif