/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:21:39 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/04 20:24:09 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_philosophers(t_sim *sim, t_philo *philo, int i)
{
	philo->eaten_count = 0;
	philo->id = i;
	philo->last_eat_at = sim->start_time;
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
	memset(sim->philosophers, 0, sizeof(t_philo) * sim->count);
	return (1);
}

t_bool	is_philo_n_dead(t_sim *sim, int n)
{
	t_bool	ret;

	pthread_mutex_lock(&sim->philosophers[n].lock);
	ret = (time_now() - sim->philosophers[n].last_eat_at > sim->time_to_die);
	pthread_mutex_unlock(&sim->philosophers[n].lock);
	return (ret);
}

t_bool	n_philo_full(t_sim *sim, int n)
{
	if (sim->philosophers[n].eaten_count >= sim->must_eat_count)
		return (true);
	return (false);
}

void	all_full(t_sim *sim)
{
	pthread_mutex_lock(&sim->m_all_eaten);
	sim->all_eaten = true;
	pthread_mutex_unlock(&sim->m_all_eaten);
}

void	check_death(t_sim *sim)
{
	int	i;
	int	j;

	while (!sim->all_eaten && !sim->end)
	{
		usleep(800);
		i = -1;
		j = 0;
		while (++i < sim->count)
		{
			if (n_philo_full(sim, i))
				j++;
		}
		if (j == sim->count)
			all_full(sim);
		i = -1;
		while (++i < sim->count)
		{
			if (is_philo_n_dead(sim, i))
			{
				print_dead(sim, DIED, i);
				pthread_mutex_lock(&sim->m_end);
				sim->end = true;
				pthread_mutex_unlock(&sim->m_end);
			}
		}
	}
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
	if (err)
		free(sim->philosophers);
	check_death(sim);
	return (err == 0);
}
