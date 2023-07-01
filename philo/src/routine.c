/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:22:40 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/01 21:23:43 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	has_eaten_enought(t_philo *philo, t_sim *sim)
{
	if (sim->must_eat_count > 0 && philo->eaten_count >= sim->must_eat_count)
		return (1);
	return (0);
}

int	check_eaten_count(t_philo *philo, t_sim *sim)
{
	pthread_mutex_lock(&sim->sim);
	pthread_mutex_lock(&philo->lock);
	if (has_eaten_enought(philo, sim))
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
	if (sim->end || has_eaten_enought(philo, sim))
	{
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_unlock(&sim->sim);
		return (1);
	}
	if (philo->last_eat_at > 0 || sim->count == 1)
	{
		time_diff = time_diff_ms(philo->last_eat_at, time_now());
		if (time_diff >= sim->time_to_die)
		{
			print_dead(sim, DIED, philo->id);
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
		usleep(200);
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
	if (philo->id % 2 != 0)
		sleep_ms(sim->time_to_eat / 2);
	if (sim->count == 1)
		sim_print(sim, TOOK_FORK, philo->id);
	pthread_create(&reaper_thread, NULL, &p_reaper, philo);
	while (sim->count > 1 && !sim_end(sim) && !check_eaten_count(philo, sim))
	{
		p_eat(sim, philo);
		p_sleep(sim, philo);
		p_think(sim, philo);
		if (sim->count % 2)
			sleep_ms(sim->time_to_eat);
	}
	pthread_join(reaper_thread, NULL);
	return (NULL);
}
