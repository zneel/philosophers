/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 09:27:31 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/09 18:49:42 by ebouvier         ###   ########.fr       */
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

enum					e_state
{
	EAT,
	SLEEP,
	THINK,
	DEAD,
};

typedef struct s_philo
{
	int					id;
	int					ret;
	pthread_t			thread;
	long long			last_eat_at;
	int					dead;
	int					eaten_count;
	t_sim				*sim;
	pthread_mutex_t		mutex;
	pthread_mutex_t		lock;
	enum e_state		state;
}						t_philo;

struct					s_sim
{
	int					count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
	pthread_mutex_t		sim;
	pthread_mutex_t		print;
	int					end;
	long long			start_time;
	t_philo				*philosophers;
	pthread_mutex_t		*forks;
};

int						alloc_forks(t_sim *sim);
int						pick_up_forks(t_sim *sim, t_philo *philo);
void					release_forks(t_sim *sim, t_philo *philo);
int						init_forks(t_sim *sim);
void					destroy_fork_mutex(pthread_mutex_t *forks, int count);

int						alloc_philosophers(t_sim *sim);
int						init_philosophers(t_sim *sim);
int						is_dead(t_sim *sim, t_philo *philo);

void					init_simulation(t_sim *philo);
void					destroy_simulation(t_sim *philo);
int						simulate(t_sim *sim);

void					print_usage(void);
void					debug_sim(t_sim *sim);
void					debug_philo(t_philo *philo);
void					sim_print(t_sim *sim, char *data, int id);
void					ft_swap(int *a, int *b);

long long				time_to_ms(t_timeval time);
long long				time_now(void);
int						sleep_ms(long long ms);
long long				time_diff_ms(long long a, long long b);

void					*p_routine(void *data);
void					p_dead(t_sim *sim, t_philo *philo);
void					p_eat(t_sim *sim, t_philo *philo);
void					p_think(t_sim *sim, t_philo *philo);
void					p_sleep(t_sim *sim, t_philo *philo);

#endif