/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:18:47 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/07 15:49:00 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_eat(t_sim *sim, t_philo *philo)
{
	sem_wait(sim->s_forks);
	sim_print(sim, TOOK_FORK, philo->id);
	sem_wait(sim->s_forks);
	sim_print(sim, TOOK_FORK, philo->id);
	sim_print(sim, EATING, philo->id);
	philo->eaten_count++;
	philo->last_eat_at = time_now();
	sleep_ms(sim->time_to_eat);
	sem_post(sim->s_forks);
	sem_post(sim->s_forks);
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
