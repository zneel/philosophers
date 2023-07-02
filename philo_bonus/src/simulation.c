/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 00:52:40 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/02 02:42:43 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_simulation(t_sim *sim)
{
	sim->philosophers = NULL;
	sim->start_time = time_now();
	sim->end = 0;
	sim->forks = sem_open("forks", O_CREAT, 0644, sim->count);
	sim->print = sem_open("print", O_CREAT, 0644, 1);
	sim->sim = sem_open("sim", O_CREAT, 0644, 1);
}

void	destroy_semaphores(t_sim *sim)
{
	if (sim->forks && (sem_close(sim->forks) == -1) && sem_unlink("forks") ==
		-1)
		printf("Error closing semaphore\n");
	if (sim->print && (sem_close(sim->print) == -1) && sem_unlink("print") ==
		-1)
		printf("Error closing semaphore\n");
	if (sim->sim && (sem_close(sim->sim) == -1) && sem_unlink("sim") == -1)
		printf("Error closing semaphore\n");
}

void	destroy_simulation(t_sim *sim)
{
	destroy_semaphores(sim);
	// destroy_semaphore();
}

void	wait_for_processes(t_sim *sim)
{
	int	i;
	int	status;

	i = 0;
	while (i < sim->count)
	{
		waitpid(sim->philosophers[i].pid, &status, 0);
		if (WIFEXITED(status))
		{
			sem_wait(sim->sim);
			sim->end = 1;
			sem_post(sim->sim);
		}
		i++;
	}
}

int	simulate(t_sim *sim)
{
	init_simulation(sim);
	if (!alloc_philosophers(sim))
		return (1);
	if (!init_forks(sim))
		return (free(sim->forks), free(sim->philosophers), 1);
	if (!init_philosophers(sim))
	{
		destroy_semaphores(sim);
		free(sim->forks);
		free(sim->philosophers);
		return (1);
	}
	wait_for_processes(sim);
	destroy_simulation(sim);
	return (0);
}