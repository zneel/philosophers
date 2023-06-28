/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:21:39 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/28 21:47:27 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_sim *sim, t_philo *philo)
{
	long long	now;

	now = time_now();
	if (philo->last_eat_at > 0 && time_diff_ms(philo->last_eat_at,
			now) >= sim->time_to_die)
		philo->dead = 1;
	return (philo->dead);
}

void	assign_philosophers(t_sim *sim, t_philo *philo, int i)
{
	philo->eaten_count = 0;
	philo->id = i;
	philo->last_eat_at = 0;
	philo->ret = 0;
	philo->dead = 0;
	philo->sim = sim;
	philo->state = THINK;
	pthread_mutex_init(&philo->mutex, NULL);
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
