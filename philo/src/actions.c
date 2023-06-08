/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:18:47 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/08 14:33:38 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief 
 * A philosophers always take his fork and the one at his left
 * @param sim 
 * @param philo 
 */
void	p_eat(t_sim *sim, t_tphilo *philo)
{
	long long	elapsed;
	long long	now;

	if (is_dead(sim, philo))
		return ;
	if (philo->state == THINK)
	{
		now = time_now();
		elapsed = time_diff_ms(sim->start_time, now);
		philo->state = EAT;
		pick_up_release_forks(sim, philo);
		printf(EATING, elapsed, philo->id);
		philo->last_eat_at = time_now();
		philo->eaten_count++;
		sleep_ms(sim->time_to_eat);
	}
}

void	p_think(t_sim *sim, t_tphilo *philo)
{
	long long	elapsed;
	long long	now;

	if (is_dead(sim, philo))
		return ;
	if (philo->state == SLEEP)
	{
		now = time_now();
		elapsed = time_diff_ms(sim->start_time, now);
		philo->state = THINK;
		printf(THINKING, elapsed, philo->id);
	}
}

int	p_dead(t_sim *sim, t_tphilo *philo)
{
	long long	elapsed;
	long long	now;

	if (is_dead(sim, philo))
	{
		now = time_now();
		elapsed = time_diff_ms(sim->start_time, now);
		philo->state = DEAD;
		philo->dead = 1;
		printf(DIED, elapsed, philo->id);
		while (!pthread_mutex_lock(&sim->sim))
			;
		sim->end = 1;
		while (!pthread_mutex_unlock(&sim->sim))
			;
		exit(1);
	}
	return (1);
}

void	p_sleep(t_sim *sim, t_tphilo *philo)
{
	long long	elapsed;
	long long	now;

	if (is_dead(sim, philo))
		return ;
	if (philo->state == EAT)
	{
		now = time_now();
		elapsed = time_diff_ms(sim->start_time, now);
		philo->state = SLEEP;
		printf(SLEEPING, elapsed, philo->id);
		sleep_ms(sim->time_to_sleep);
	}
}
