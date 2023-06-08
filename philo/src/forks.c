/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:47:26 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/08 14:02:28 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_up_release_forks(t_sim *sim, t_tphilo *philo)
{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	int				philo_idx;

	philo_idx = philo->id - 1;
	left = sim->forks[(philo_idx - 1) % sim->count];
	right = sim->forks[philo_idx];
	while (!pthread_mutex_lock(left) && !is_dead(sim, philo))
		;
	printf(TOOK_FORK, time_now(), philo->id);
	while (!pthread_mutex_lock(right) && !is_dead(sim, philo))
		;
	printf(TOOK_FORK, time_now(), philo->id);
	while (!pthread_mutex_unlock(left) && !is_dead(sim, philo))
		;
	while (!pthread_mutex_unlock(right) && !is_dead(sim, philo))
		;
	return (1);
}

void	destroy_forks(pthread_mutex_t **forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(forks[i++]);
	free(forks);
}

void	destroy_fork_mutex(pthread_mutex_t **forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(forks[i]);
		i++;
	}
}

int	alloc_forks(t_sim *sim)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	sim->forks = malloc(sizeof(pthread_mutex_t *) * sim->count);
	if (!sim->forks)
		return (1);
	while (i < sim->count)
	{
		sim->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!sim->forks[i])
		{
			err = 1;
			break ;
		}
		i++;
	}
	if (err)
		destroy_forks(sim->forks, i);
	return (err);
}

int	init_forks(t_sim *sim)
{
	int	i;
	int	err;

	i = 0;
    err = 0;
	while (i < sim->count)
	{
		err = pthread_mutex_init(sim->forks[i], NULL);
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
        destroy_forks(sim->forks, i);
    }
	return (err);
}
