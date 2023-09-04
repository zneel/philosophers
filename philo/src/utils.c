/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 00:13:53 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/04 19:40:49 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	print_dead(t_sim *sim, char *data, int id)
{
	pthread_mutex_lock(&sim->m_print);
	printf(data, time_diff_ms(sim->start_time, time_now()), id + 1);
	pthread_mutex_unlock(&sim->m_print);
}

void	sim_print(t_sim *sim, char *data, int id)
{
	pthread_mutex_lock(&sim->m_end);
	if (!sim->end)
	{
		pthread_mutex_lock(&sim->m_print);
		printf(data, time_diff_ms(sim->start_time, time_now()), id + 1);
		pthread_mutex_unlock(&sim->m_print);
	}
	pthread_mutex_unlock(&sim->m_end);
}

int	sim_end(t_sim *sim)
{
	pthread_mutex_lock(&sim->m_end);
	if (sim->end)
	{
		pthread_mutex_unlock(&sim->m_end);
		return (1);
	}
	pthread_mutex_unlock(&sim->m_end);
	return (0);
}
