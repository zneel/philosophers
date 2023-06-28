/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:47:26 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/28 21:47:24 by ebouvier         ###   ########.fr       */
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
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % sim->count;
	if (left > right)
		ft_swap(&left, &right);
	pthread_mutex_lock(&sim->forks[left]);
	sim_print(sim, TOOK_FORK, philo->id);
	pthread_mutex_lock(&sim->forks[right]);
	sim_print(sim, TOOK_FORK, philo->id);
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
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % sim->count;
	if (left > right)
		ft_swap(&left, &right);
	pthread_mutex_unlock(&sim->forks[right]);
	pthread_mutex_unlock(&sim->forks[left]);
}

void	destroy_fork_mutex(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
		pthread_mutex_destroy(&forks[i++]);
}

int	alloc_forks(t_sim *sim)
{
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
