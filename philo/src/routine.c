/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:22:40 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/29 15:58:02 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eaten_count(t_philo *philo, t_sim *sim)
{
	pthread_mutex_lock(&sim->sim);
	pthread_mutex_lock(&philo->lock);
	if (sim->must_eat_count > 0 && philo->eaten_count >= sim->must_eat_count)
	{
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_unlock(&sim->sim);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&sim->sim);
	return (0);
}

int	check_dead(t_philo *philo, t_sim *sim)
{
	long long	time_diff;

	pthread_mutex_lock(&sim->sim);
	pthread_mutex_lock(&philo->lock);
	if (sim->end)
	{
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_unlock(&sim->sim);
		return (1);
	}
	if (philo->last_eat_at > 0)
	{
		time_diff = time_diff_ms(philo->last_eat_at, time_now());
		if (time_diff >= sim->time_to_die)
		{
			sim_print(sim, DIED, philo->id);
			sim->end = 1;
			pthread_mutex_unlock(&philo->lock);
			pthread_mutex_unlock(&sim->sim);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&sim->sim);
	return (0);
}

void	*p_reaper(void *data)
{
	t_philo	*philo;
	t_sim	*sim;

	philo = (t_philo *)data;
	sim = philo->sim;
	while (1)
	{
		if (check_dead(philo, sim))
			break ;
		sleep_ms(sim->time_to_die / 10);
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
	while (1)
	{
		pthread_mutex_lock(&sim->sim);
		if (sim->end)
		{
			pthread_mutex_unlock(&sim->sim);
			break ;
		}
		pthread_mutex_unlock(&sim->sim);
		if (check_eaten_count(philo, sim))
			return (NULL);
		p_eat(sim, philo);
		p_sleep(sim, philo);
		p_think(sim, philo);
	}
	pthread_join(reaper_thread, NULL);
	return (NULL);
}
