/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:21:39 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/05 15:37:08 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_philosophers(t_sim *sim, t_philo *philo, int i)
{
	pthread_mutex_init(&philo->m_last_eat_at, NULL);
	pthread_mutex_init(&philo->m_eaten_count, NULL);
	pthread_mutex_init(&philo->m_stop, NULL);
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
		sim->philosophers[i].ret = pthread_create(&sim->philosophers[i].thread,
				NULL, &p_routine, &sim->philosophers[i]);
		if (sim->philosophers[i].ret)
		{
			err = sim->philosophers[i].ret;
			printf("Error initializing thread\n");
			break ;
		}
		i++;
	}
	pthread_create(&sim->t_check, NULL, &p_check, sim);
	if (err)
		free(sim->philosophers);
	return (err == 0);
}
