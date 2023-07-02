/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:05:37 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/02 02:46:58 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	has_eaten_enought(t_philo *philo, t_sim *sim)
{
	if (sim->must_eat_count > 0 && philo->eaten_count >= sim->must_eat_count)
		return (1);
	return (0);
}

int	check_eaten_count(t_philo *philo, t_sim *sim)
{
	sem_wait(sim->sim);
	if (has_eaten_enought(philo, sim))
	{
		sem_post(sim->sim);
		return (1);
	}
	sem_post(sim->sim);
	return (0);
}

int	check_dead(t_philo *philo, t_sim *sim)
{
	long long	time_diff;

	sem_wait(sim->sim);
	sem_wait(philo->lock);
	if (sim->end || has_eaten_enought(philo, sim))
	{
		sem_post(philo->lock);
		sem_post(sim->sim);
		return (1);
	}
	if (philo->last_eat_at > 0 || sim->count == 1)
	{
		time_diff = time_diff_ms(philo->last_eat_at, time_now());
		if (time_diff >= sim->time_to_die)
		{
			print_dead(sim, DIED, philo->id);
			sim->end = 1;
			sem_post(philo->lock);
			sem_post(sim->sim);
			return (1);
		}
	}
	sem_post(philo->lock);
	sem_post(sim->sim);
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
		{
			kill(philo->pid, SIGKILL);
			return (NULL);
		}
		usleep(200);
	}
	return (NULL);
}

void	*p_routine(t_sim *sim, t_philo *philo)
{
	pthread_t reaper_thread;

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