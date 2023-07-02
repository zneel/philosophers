/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:01:59 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/02 02:36:31 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	assign_philosophers(t_sim *sim, t_philo *philo, int i)
{
	char	*str;

	str = ft_itoa(i);
	if (!str)
		return ;
	philo->id = i;
	philo->eaten_count = 0;
	philo->pid = -1;
	philo->last_eat_at = sim->start_time;
	philo->dead = 0;
	philo->sim = sim;
	philo->lock = sem_open(str, O_CREAT, 0644, 1);
	free(str);
}

int	alloc_philosophers(t_sim *sim)
{
	sim->philosophers = malloc(sizeof(t_philo) * sim->count);
	if (!sim->philosophers)
		return (0);
	memset(sim->philosophers, 0, sizeof(t_philo) * sim->count);
	return (1);
}

void	destroy_philo_semaphores(t_philo *philo)
{
	char	*str;

	str = ft_itoa(philo->id);
	if (!str)
		return ;
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
