/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:49:46 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/30 23:20:25 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_simulation(t_sim *sim)
{
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

void	wait_for_threads(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->count)
	{
		if (pthread_join(sim->philosophers[i].thread, NULL) != 0)
			printf("Error joining thread\n");
		i++;
	}
}

int	simulate(t_sim *sim)
{
	init_simulation(sim);
	if (!alloc_philosophers(sim))
		return (1);
	if (!alloc_forks(sim))
		return (free(sim->philosophers), 1);
	if (!init_forks(sim))
		return (free(sim->forks), free(sim->philosophers), 1);
	if (!init_philosophers(sim))
	{
		destroy_fork_mutex(sim->forks, sim->count);
		free(sim->forks);
		free(sim->philosophers);
		pthread_mutex_destroy(&sim->sim);
		pthread_mutex_destroy(&sim->print);
		return (1);
	}
	wait_for_threads(sim);
	destroy_simulation(sim);
	return (0);
}
