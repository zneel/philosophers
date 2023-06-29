/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:18:47 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/29 16:25:56 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_eat(t_sim *sim, t_philo *philo)
{
	pick_up_forks(sim, philo);
	pthread_mutex_lock(&philo->lock);
	philo->last_eat_at = time_now();
	pthread_mutex_unlock(&philo->lock);
	if (!sim_end(sim))
		sim_print(sim, EATING, philo->id);
	philo->eaten_count++;
	sleep_ms(sim->time_to_eat);
	release_forks(sim, philo);
}

void	p_think(t_sim *sim, t_philo *philo)
{
	if (!sim_end(sim))
		sim_print(sim, THINKING, philo->id);
}

void	p_sleep(t_sim *sim, t_philo *philo)
{
	if (!sim_end(sim))
		sim_print(sim, SLEEPING, philo->id);
	sleep_ms(sim->time_to_sleep);
}
