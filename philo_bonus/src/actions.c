/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:18:08 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/02 01:31:22 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	p_eat(t_sim *sim, t_philo *philo)
{
	sem_wait(sim->forks);
	sim_print(sim, TOOK_FORK, philo->id);
	sem_wait(sim->forks);
	sim_print(sim, TOOK_FORK, philo->id);
	sim_print(sim, EATING, philo->id);
	philo->last_eat_at = time_now();
	philo->eaten_count++;
	sleep_ms(sim->time_to_eat);
	sem_post(sim->forks);
	sem_post(sim->forks);
}

void	p_think(t_sim *sim, t_philo *philo)
{
	sim_print(sim, THINKING, philo->id);
}

void	p_sleep(t_sim *sim, t_philo *philo)
{
	sim_print(sim, SLEEPING, philo->id);
	sleep_ms(sim->time_to_sleep);
}