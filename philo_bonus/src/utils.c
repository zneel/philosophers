/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 00:13:53 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/07 15:14:44 by ebouvier         ###   ########.fr       */
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
	sem_wait(sim->s_print);
	printf(data, time_diff_ms(sim->start_time, time_now()), id + 1);
	sem_post(sim->s_print);
}

void	sim_print(t_sim *sim, char *data, int id)
{
	sem_wait(sim->s_end);
	sem_wait(sim->s_print);
	if (!sim->end)
		printf(data, time_diff_ms(sim->start_time, time_now()), id + 1);
	sem_post(sim->s_print);
	sem_post(sim->s_end);
}

t_bool	sim_end(t_sim *sim)
{
	sem_wait(sim->s_end);
	if (sim->end)
	{
		sem_post(sim->s_end);
		return (true);
	}
	sem_post(sim->s_end);
	return (false);
}
