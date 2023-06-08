/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:21:39 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/08 14:12:25 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_sim *sim, t_tphilo *philo)
{
	long long	now;

	now = time_now();
	printf("time now=%lld\n", now);
	if (time_diff_ms(philo->last_eat_at, now) >= sim->time_to_die)
		philo->dead = 1;
	return (philo->dead);
}

void	destroy_philosophers(t_tphilo **tphilos, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(tphilos[i++]);
	free(tphilos);
}

void	assign_philosophers(t_tphilo *philo, int i)
{
	philo->eaten_count = 0;
	philo->id = i + 1;
	philo->last_eat_at = time_now();
	philo->ret = 0;
	philo->dead = 0;
	philo->state = THINK;
}

int	alloc_philosophers(t_sim *sim)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	sim->philosophers = malloc(sizeof(t_tphilo *) * sim->count);
	if (!sim->philosophers)
		return (0);
	while (i < sim->count)
	{
		sim->philosophers[i] = malloc(sizeof(t_tphilo));
		if (!sim->philosophers[i])
		{
			err = 1;
			break ;
		}
		i++;
	}
	if (err)
		destroy_philosophers(sim->philosophers, i);
	return (err);
}

int	init_philosophers(t_sim *sim)
{
	int		i;
	t_args	args;
	int		err;

	i = 0;
	err = 0;
	while (i < sim->count)
	{
		args.philo = sim->philosophers[i];
		args.sim = sim;
		assign_philosophers(sim->philosophers[i], i);
		sim->philosophers[i]->ret = pthread_create(
			&sim->philosophers[i]->thread, NULL, &p_routine, &args);
		if (sim->philosophers[i]->ret)
		{
			err = sim->philosophers[i]->ret;
			printf("Error initializing thread\n");
			break ;
		}
		i++;
	}
	if (err)
		destroy_philosophers(sim->philosophers, i);
	return (err);
}
