/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:49:46 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/08 14:20:57 by ebouvier         ###   ########.fr       */
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
}

void	destroy_simulation(t_sim *sim)
{
	destroy_fork_mutex(sim->forks, sim->count);
	destroy_forks(sim->forks, sim->count);
	destroy_philosophers(sim->philosophers, sim->count);
	pthread_mutex_destroy(&sim->sim);
}

int	simulate(t_sim *sim)
{
	int	i;

	i = 0;
	debug_sim(sim);
	if (alloc_philosophers(sim) > 0 || init_philosophers(sim) > 0)
		return (1);
	if (alloc_forks(sim) > 0 || init_forks(sim) > 0)
		return (1);
	while (i < sim->count)
		pthread_detach(sim->philosophers[i++]->thread);
	destroy_simulation(sim);
	return (0);
}
