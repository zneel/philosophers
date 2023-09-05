/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:22:40 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/05 15:42:08 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	has_eaten_enought(t_philo *philo)
{
	if (philo->must_eat_count > 0
		&& philo->eaten_count >= philo->must_eat_count)
		return (true);
	return (false);
}

t_bool	should_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_stop);
	if (philo->stop)
	{
		pthread_mutex_unlock(&philo->m_stop);
		return (true);
	}
	pthread_mutex_unlock(&philo->m_stop);
	return (false);
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
	{
		sim_print(sim, TOOK_FORK, philo->id);
		sleep_ms(sim->time_to_die);
	}
	if (philo->id % 2 == 0)
		sleep_ms(1);
	while (sim->count > 1 && !sim_end(sim) && !should_stop(philo))
	{
		p_eat(sim, philo);
		p_sleep(sim, philo);
		p_think(sim, philo);
		if (sim->count % 2)
			sleep_ms(sim->time_to_eat);
	}
	return (NULL);
}
