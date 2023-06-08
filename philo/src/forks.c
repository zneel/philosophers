/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:47:26 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/08 18:31:51 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief 
 * The philosopher always take his fork and the one at his right
 * @param sim 
 * @param philo 
 * @return int 
 */
int	pick_up_forks(t_sim *sim, t_philo *philo)
{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	int				philo_idx;
	long long		now;

	philo_idx = philo->id;
	pthread_mutex_lock(&sim->fork);
	left = &sim->forks[philo_idx];
	right = &sim->forks[(philo_idx + 1) % sim->count];
	now = time_now();
	pthread_mutex_lock(right);
	printf(TOOK_FORK, time_diff_ms(sim->start_time, now), philo->id + 1);
	pthread_mutex_lock(left);
	printf(TOOK_FORK, time_diff_ms(sim->start_time, now), philo->id + 1);
	pthread_mutex_unlock(&sim->fork);
	return (1);
}

/**
 * @brief 
 * Release forks 
 * @param sim 
 * @param philo 
 */
void	release_forks(t_sim *sim, t_philo *philo)
{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	int				philo_idx;

	philo_idx = philo->id;
	right = &sim->forks[philo_idx];
	left = &sim->forks[(philo_idx + 1) % sim->count];
	pthread_mutex_unlock(right);
	pthread_mutex_unlock(left);
}

void	destroy_fork_mutex(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	alloc_forks(t_sim *sim)
{
	printf("allocating %d forks \n", sim->count);
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->count);
	if (!sim->forks)
		return (0);
	return (1);
}

int	init_forks(t_sim *sim)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (i < sim->count)
	{
		err = pthread_mutex_init(&sim->forks[i], NULL);
		if (err)
		{
			printf("Error initializing mutex\n");
			break ;
		}
		i++;
	}
	if (err)
	{
		destroy_fork_mutex(sim->forks, i);
		free(sim->forks);
	}
	return (err);
}
