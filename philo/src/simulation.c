/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:49:46 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/08 18:15:01 by ebouvier         ###   ########.fr       */
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
	pthread_mutex_init(&sim->fork, NULL);
}

void	destroy_simulation(t_sim *sim)
{
	destroy_fork_mutex(sim->forks, sim->count);
	free(sim->forks);
	free(sim->philosophers);
	pthread_mutex_destroy(&sim->sim);
	pthread_mutex_destroy(&sim->fork);
}

int	simulate(t_sim *sim)
{
	int	i;

	i = 0;
	debug_sim(sim);
	alloc_philosophers(sim);
	alloc_forks(sim);
	init_forks(sim);
	init_philosophers(sim);
	while (i < sim->count)
		pthread_join(sim->philosophers[i++].thread, NULL);
	destroy_simulation(sim);
	return (0);
}
