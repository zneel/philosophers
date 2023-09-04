/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:22:40 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/04 19:50:41 by ebouvier         ###   ########.fr       */
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
	pthread_mutex_lock(&sim->m_eat_count);
	pthread_mutex_lock(&philo->lock);
	if (has_eaten_enought(philo, sim))
	{
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_unlock(&sim->m_eat_count);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&sim->m_eat_count);
	return (0);
}

void	*p_routine(void *data)
{
	t_sim	*sim;
	t_philo	*philo;

	sim = ((t_philo *)data)->sim;
	philo = ((t_philo *)data);
	if (philo->id % 2 != 0)
		sleep_ms(sim->time_to_eat / 2);
	if (sim->count == 1)
		sim_print(sim, TOOK_FORK, philo->id);
	while (sim->count > 1 && !sim_end(sim) && !check_eaten_count(philo, sim))
	{
		p_eat(sim, philo);
		p_sleep(sim, philo);
		p_think(sim, philo);
	}
	return (NULL);
}
