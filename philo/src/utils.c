/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 00:13:53 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/28 21:47:33 by ebouvier         ###   ########.fr       */
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

void	sim_print(t_sim *sim, char *data, int id)
{
	pthread_mutex_lock(&sim->sim);
	if (!sim->end)
	{
		pthread_mutex_unlock(&sim->sim);
		pthread_mutex_lock(&sim->print);
		printf(data, time_diff_ms(sim->start_time, time_now()), id + 1);
		pthread_mutex_unlock(&sim->print);
	}
	else
	{
		pthread_mutex_unlock(&sim->sim);
	}
}
