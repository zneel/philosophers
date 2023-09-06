/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:49:46 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/06 18:03:40 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_simulation(void)
{
	sem_unlink("s_all_eaten");
	sem_unlink("s_eat_count");
	sem_unlink("s_print");
	sem_unlink("s_end");
	sem_unlink("s_sim");
	sem_unlink("s_forks");
}

void	init_simulation(t_sim *sim)
{
	sim->philosophers = NULL;
	sim->start_time = time_now();
	sim->end = false;
	sim->all_eaten = false;
	sim->t_check = 0;
	sim->s_forks = sem_open("s_forks", O_CREAT, 0644, sim->count);
	sim->s_all_eaten = sem_open("s_all_eaten", O_CREAT, 0644, 1);
	sim->s_eat_count = sem_open("s_eat_count", O_CREAT, 0644, 1);
	sim->s_print = sem_open("s_print", O_CREAT, 0644, 1);
	sim->s_end = sem_open("s_end", O_CREAT, 0644, 1);
	sim->s_sim = sem_open("s_sim", O_CREAT, 0644, 1);
	if (sim->s_all_eaten == SEM_FAILED || sim->s_eat_count == SEM_FAILED
		|| sim->s_print == SEM_FAILED || sim->s_end == SEM_FAILED
		|| sim->s_sim == SEM_FAILED || sim->s_forks == SEM_FAILED)
	{
		printf("Error creating semaphore\n");
		clear_simulation();
		exit(1);
	}
}

void	destroy_simulation(t_sim *sim)
{
	if (sim->s_forks && (sem_close(sim->s_forks) == -1)
		&& sem_unlink("s_forks") == -1)
		printf("Error closing semaphore\n");
	if (sim->s_print && (sem_close(sim->s_print) == -1)
		&& sem_unlink("s_print") == -1)
		printf("Error closing semaphore\n");
	if (sim->s_sim && (sem_close(sim->s_sim) == -1) && sem_unlink("s_sim") ==
		-1)
		printf("Error closing semaphore\n");
	if (sim->s_end && (sem_close(sim->s_end) == -1) && sem_unlink("s_end") ==
		-1)
		printf("Error closing semaphore\n");
	if (sim->s_all_eaten && (sem_close(sim->s_all_eaten) == -1)
		&& sem_unlink("s_all_eaten") == -1)
		printf("Error closing semaphore\n");
	if (sim->s_eat_count && (sem_close(sim->s_eat_count) == -1)
		&& sem_unlink("s_eat_count") == -1)
		printf("Error closing semaphore\n");
}

void	wait_for_processes(t_sim *sim)
{
	int	i;
	int	status;

	i = 0;
	while (i < sim->count)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
			i = 0;
		i++;
	}
}

int	simulate(t_sim *sim)
{
	init_simulation(sim);
	if (!alloc_philosophers(sim))
		return (1);
	if (!init_forks(sim))
		return (free(sim->philosophers), 1);
	if (!init_philosophers(sim))
	{
		destroy_simulation(sim);
		return (1);
	}
	wait_for_processes(sim);
	pthread_join(sim->t_check, NULL);
	destroy_simulation(sim);
	return (0);
}
