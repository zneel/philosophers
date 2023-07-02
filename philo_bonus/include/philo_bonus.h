/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:44:40 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/02 02:40:35 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "libft.h"
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
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

typedef struct s_philo
{
	int					id;
	pid_t				pid;
	long long			last_eat_at;
	int					dead;
	int					eaten_count;
	t_sim				*sim;
	sem_t				*lock;
}						t_philo;

struct					s_sim
{
	int					count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
	int					end;
	long long			start_time;
	t_philo				*philosophers;
	sem_t				*sim;
	sem_t				*forks;
	sem_t				*print;
};

void					print_usage(void);
long long				time_to_ms(t_timeval time);
long long				time_now(void);
long long				time_diff_ms(long long a, long long b);
int						sleep_ms(long long ms);
int						sim_end(t_sim *sim);
void					sim_print(t_sim *sim, char *data, int id);
void					print_dead(t_sim *sim, char *data, int id);
void					*p_routine(t_sim *sim, t_philo *philo);
void					p_eat(t_sim *sim, t_philo *philo);
void					p_think(t_sim *sim, t_philo *philo);
void					p_sleep(t_sim *sim, t_philo *philo);
int						init_philosophers(t_sim *sim);
int						alloc_philosophers(t_sim *sim);
int						init_forks(t_sim *sim);
int						simulate(t_sim *sim);
#endif