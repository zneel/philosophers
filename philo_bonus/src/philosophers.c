/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:21:39 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/07 14:40:56 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_philosophers(t_sim *sim, t_philo *philo, int i)
{
	philo->eaten_count = 0;
	philo->id = i;
	philo->last_eat_at = sim->start_time;
	philo->must_eat_count = sim->must_eat_count;
	philo->ret = 0;
	philo->stop = false;
	philo->dead = false;
	philo->sim = sim;
}

int	alloc_philosophers(t_sim *sim)
{
	sim->philosophers = malloc(sizeof(t_philo) * sim->count);
	if (!sim->philosophers)
		return (0);
	memset(sim->philosophers, 0, sizeof(t_philo) * sim->count);
	return (1);
}

int	init_philosophers(t_sim *sim)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (i < sim->count)
	{
		assign_philosophers(sim, &sim->philosophers[i], i);
		sim->philosophers[i].pid = fork();
		if (sim->philosophers[i].pid == -1)
		{
			err = sim->philosophers[i].pid;
			printf("Error initializing fork\n");
			break ;
		}
		else if (sim->philosophers[i].pid == 0)
			p_routine(sim, &sim->philosophers[i]);
		i++;
	}
	if (err == -1)
		free(sim->philosophers);
	return (err == 0);
}
