/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:22:40 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/28 21:47:28 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_reaper(void *data)
{
	t_philo		*philo;
	t_sim		*sim;
	long long	time_diff;

	philo = (t_philo *)data;
	sim = philo->sim;
	while (1)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->last_eat_at > 0)
		{
			time_diff = time_diff_ms(philo->last_eat_at, time_now());
			pthread_mutex_unlock(&philo->lock);
			if (time_diff >= sim->time_to_die)
			{
				pthread_mutex_lock(&sim->sim);
				sim->end = 1;
				pthread_mutex_unlock(&sim->sim);
				sim_print(sim, DIED, philo->id);
				break ;
			}
		}
		pthread_mutex_unlock(&philo->lock);
		usleep(sim->time_to_die);
	}
	return (NULL);
}

void	*p_routine(void *data)
{
	t_sim		*sim;
	t_philo		*philo;
	pthread_t	reaper_thread;

	sim = ((t_philo *)data)->sim;
	philo = ((t_philo *)data);
	pthread_create(&reaper_thread, NULL, &p_reaper, philo);
	while (!sim->end && !is_dead(sim, philo))
	{
		pthread_mutex_lock(&sim->sim);
		if (sim->end)
		{
			pthread_mutex_unlock(&sim->sim);
			break ;
		}
		pthread_mutex_unlock(&sim->sim);
		p_eat(sim, philo);
		p_think(sim, philo);
		p_sleep(sim, philo);
	}
	pthread_join(reaper_thread, NULL);
	return (NULL);
}
