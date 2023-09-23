/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:22:40 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/07 16:54:29 by ebouvier         ###   ########.fr       */
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
	if (philo->stop)
		return (true);
	return (false);
}

void	*p_check(void *arg)
{
	t_philo		*philo;
	long long	last_eat_at;

	philo = (t_philo *)arg;
	while (true)
	{
		if (philo->sim->end || philo->stop)
			return (NULL);
		last_eat_at = time_diff_ms(time_now(), philo->last_eat_at);
		if (last_eat_at >= philo->sim->time_to_die && !has_eaten_enought(philo))
		{
			sem_wait(philo->sim->s_end);
			philo->sim->end = true;
			philo->dead = true;
			print_dead(philo->sim, DIED, philo->id);
			sem_post(philo->sim->s_end);
			return (NULL);
		}
		if (has_eaten_enought(philo))
			return (NULL);
		usleep(200);
	}
	return (NULL);
}

void	*p_routine(t_sim *sim, t_philo *philo)
{
	pthread_t	t_check;

	pthread_create(&t_check, NULL, p_check, philo);
	if (philo->id % 2 != 0)
		sleep_ms(sim->time_to_eat / 2);
	if (sim->count == 1)
		sim_print(sim, TOOK_FORK, philo->id);
	while (!philo->dead && sim->count > 1 && !sim_end(sim)
		&& !should_stop(philo))
	{
		p_eat(sim, philo);
		p_sleep(sim, philo);
		p_think(sim, philo);
		if (sim->count % 2)
			sleep_ms(sim->time_to_eat);
	}
	pthread_join(t_check, NULL);
	return (NULL);
}
