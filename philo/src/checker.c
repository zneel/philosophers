/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:39:51 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/05 15:38:36 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	is_philo_n_dead(t_sim *sim, int n)
{
	t_bool	ret;

	pthread_mutex_lock(&sim->philosophers[n].m_last_eat_at);
	ret = time_diff_ms(sim->philosophers[n].last_eat_at,
			time_now()) > sim->time_to_die;
	pthread_mutex_unlock(&sim->philosophers[n].m_last_eat_at);
	if (ret)
	{
		pthread_mutex_lock(&sim->philosophers[n].m_dead);
		sim->philosophers[n].dead = true;
		pthread_mutex_unlock(&sim->philosophers[n].m_dead);
	}
	return (ret);
}

t_bool	n_philo_full(t_sim *sim, int n)
{
	pthread_mutex_lock(&sim->philosophers[n].m_eaten_count);
	if (sim->must_eat_count != -1
		&& sim->philosophers[n].eaten_count >= sim->must_eat_count)
	{
		pthread_mutex_lock(&sim->philosophers[n].m_stop);
		sim->philosophers[n].stop = true;
		pthread_mutex_unlock(&sim->philosophers[n].m_stop);
		pthread_mutex_unlock(&sim->philosophers[n].m_eaten_count);
		return (true);
	}
	pthread_mutex_unlock(&sim->philosophers[n].m_eaten_count);
	return (false);
}

void	all_full(t_sim *sim)
{
	pthread_mutex_lock(&sim->m_all_eaten);
	sim->all_eaten = true;
	pthread_mutex_unlock(&sim->m_all_eaten);
}

void	check_death(t_sim *sim)
{
	int	i;
	int	j;

	while (!sim->all_eaten && !sim->end)
	{
		usleep(600);
		i = -1;
		j = 0;
		while (++i < sim->count)
		{
			if (n_philo_full(sim, i))
				j++;
		}
		if (j == sim->count)
			all_full(sim);
		i = 0;
		while (i < sim->count)
		{
			if (is_philo_n_dead(sim, i))
			{
				print_dead(sim, DIED, i);
				pthread_mutex_lock(&sim->m_end);
				sim->end = true;
				pthread_mutex_unlock(&sim->m_end);
				break ;
			}
			i++;
		}
	}
}

void	*p_check(void *data)
{
	t_sim	*sim;

	sim = (t_sim *)data;
	check_death(sim);
	return (NULL);
}
