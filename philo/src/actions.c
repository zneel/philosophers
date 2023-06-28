/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:18:47 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/28 21:47:18 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_eat(t_sim *sim, t_philo *philo)
{
	if (philo->state == THINK)
	{
		philo->state = EAT;
		pick_up_forks(sim, philo);
		sim_print(sim, EATING, philo->id);
		philo->last_eat_at = time_now();
		philo->eaten_count++;
		sleep_ms(sim->time_to_eat);
		release_forks(sim, philo);
	}
}

void	p_think(t_sim *sim, t_philo *philo)
{
	if (philo->state == SLEEP)
	{
		philo->state = THINK;
		sim_print(sim, THINKING, philo->id);
	}
}

void	p_dead(t_sim *sim, t_philo *philo)
{
	if (is_dead(sim, philo))
	{
		philo->state = DEAD;
		philo->dead = 1;
		sim_print(sim, DIED, philo->id);
		pthread_mutex_lock(&sim->sim);
		sim->end = 1;
		pthread_mutex_unlock(&sim->sim);
		exit(1);
	}
}

void	p_sleep(t_sim *sim, t_philo *philo)
{
	if (philo->state == EAT)
	{
		philo->state = SLEEP;
		sim_print(sim, SLEEPING, philo->id);
		sleep_ms(sim->time_to_sleep);
	}
}
