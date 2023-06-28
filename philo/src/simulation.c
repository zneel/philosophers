/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:49:46 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/28 21:47:30 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_simulation(t_sim *sim)
{
	sim->count = 0;
	sim->must_eat_count = -1;
	sim->time_to_die = 0;
	sim->time_to_eat = 0;
	sim->time_to_sleep = 0;
	sim->philosophers = NULL;
	sim->forks = NULL;
	sim->start_time = time_now();
	sim->end = 0;
	pthread_mutex_init(&sim->sim, NULL);
	pthread_mutex_init(&sim->print, NULL);
}

void	destroy_simulation(t_sim *sim)
{
	destroy_fork_mutex(sim->forks, sim->count);
	free(sim->forks);
	free(sim->philosophers);
	pthread_mutex_destroy(&sim->sim);
	pthread_mutex_destroy(&sim->print);
}
void	*schedule(void *data)
{
	t_sim		*sim;
	int			i;
	long long	current_time;

	sim = (t_sim *)data;
	while (1)
	{
		i = 0;
		current_time = time_now();
		while (i < sim->count)
		{
			pthread_mutex_lock(&sim->philosophers[i].mutex);
			if (sim->philosophers[i].state != EAT &&
				current_time
					- sim->philosophers[i].last_eat_at > sim->time_to_die)
			{
				pthread_mutex_unlock(&sim->philosophers[i].mutex);
				pthread_mutex_lock(&sim->sim);
				sim->end = 1;
				pthread_mutex_unlock(&sim->sim);
				return (NULL);
			}
			pthread_mutex_unlock(&sim->philosophers[i].mutex);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

int	simulate(t_sim *sim)
{
	int	i;

	// pthread_t	monitor_thread;
	i = 0;
	alloc_philosophers(sim);
	alloc_forks(sim);
	init_forks(sim);
	init_philosophers(sim);
	// if (pthread_create(&monitor_thread, NULL, &schedule, sim) != 0)
	// return (1);
	while (i < sim->count)
		pthread_join(sim->philosophers[i++].thread, NULL);
	// pthread_join(monitor_thread, NULL);
	destroy_simulation(sim);
	return (0);
}
