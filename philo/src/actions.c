/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:18:47 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/08 13:28:32 by ebouvier         ###   ########.fr       */
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
	if (is_dead(sim, philo))
		return ;
	if (philo->state == THINK)
	{
		philo->state = EAT;
		pick_up_release_forks(sim, philo);
		printf(EATING, philo->last_eat_at, philo->id);
		philo->last_eat_at = time_now();
		philo->eaten_count++;
	}
}

void	p_think(t_sim *sim, t_tphilo *philo)
{
	if (is_dead(sim, philo))
		return ;
	if (philo->state == SLEEP)
	{
		philo->state = THINK;
		printf(THINKING, time_now(), philo->id);
	}
}

int	p_dead(t_sim *sim, t_tphilo *philo)
{
	if (is_dead(sim, philo))
	{
		philo->state = DEAD;
		philo->dead = 1;
		printf(DIED, time_now(), philo->id);
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
	if (is_dead(sim, philo))
		return ;
	if (philo->state == EAT)
	{
		philo->state = SLEEP;
		printf(SLEEPING, time_now(), philo->id);
	}
}
