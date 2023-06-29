/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:21:39 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/29 16:14:23 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_philosophers(t_sim *sim, t_philo *philo, int i)
{
	philo->eaten_count = 0;
	philo->id = i;
	philo->last_eat_at = 0;
	philo->ret = 0;
	philo->dead = 0;
	philo->sim = sim;
	pthread_mutex_init(&philo->lock, NULL);
}

int	alloc_philosophers(t_sim *sim)
{
	sim->philosophers = malloc(sizeof(t_philo) * sim->count);
	if (!sim->philosophers)
		return (0);
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
		if (i % 2 == 0)
			sleep_ms(2);
		assign_philosophers(sim, &sim->philosophers[i], i);
		sim->philosophers[i].ret = pthread_create(&sim->philosophers[i].thread,
													NULL,
													&p_routine,
													&sim->philosophers[i]);
		if (sim->philosophers[i].ret)
		{
			err = sim->philosophers[i].ret;
			printf("Error initializing thread\n");
			break ;
		}
		i++;
	}
	if (err)
		free(sim->philosophers);
	return (err);
}
