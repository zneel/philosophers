/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:18:47 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/05 15:34:47 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_eat(t_sim *sim, t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % sim->count;
	if (right < left)
		ft_swap(&left, &right);
	pthread_mutex_lock(&sim->forks[left]);
	sim_print(sim, TOOK_FORK, philo->id);
	pthread_mutex_lock(&sim->forks[right]);
	sim_print(sim, TOOK_FORK, philo->id);
	sim_print(sim, EATING, philo->id);
	pthread_mutex_lock(&philo->m_eaten_count);
	philo->eaten_count++;
	pthread_mutex_unlock(&philo->m_eaten_count);
	pthread_mutex_lock(&philo->m_last_eat_at);
	philo->last_eat_at = time_now();
	pthread_mutex_unlock(&philo->m_last_eat_at);
	sleep_ms(sim->time_to_eat);
	pthread_mutex_unlock(&sim->forks[right]);
	pthread_mutex_unlock(&sim->forks[left]);
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
