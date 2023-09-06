/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:39:51 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/06 17:35:00 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	is_philo_n_dead(t_sim *sim, int n)
{
	t_bool	ret;

	ret = time_diff_ms(sim->philosophers[n].last_eat_at,
			time_now()) > sim->time_to_die;
	if (ret)
	{
		sim->philosophers[n].dead = true;
	}
	return (ret);
}

t_bool	n_philo_full(t_sim *sim, int n)
{
	if (sim->must_eat_count != -1
		&& sim->philosophers[n].eaten_count >= sim->must_eat_count)
	{
		sim->philosophers[n].stop = true;
		return (true);
	}
	return (false);
}

void	all_full(t_sim *sim)
{
	sem_wait(sim->s_all_eaten);
	sim->all_eaten = true;
	sem_post(sim->s_all_eaten);
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
				sem_wait(sim->s_end);
				sim->end = true;
				sem_post(sim->s_end);
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
