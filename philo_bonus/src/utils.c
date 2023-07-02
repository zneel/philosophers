/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:09:07 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/02 01:31:47 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_dead(t_sim *sim, char *data, int id)
{
	sem_wait(sim->print);
	printf(data, time_diff_ms(sim->start_time, time_now()), id + 1);
	sem_post(sim->print);
}

void	sim_print(t_sim *sim, char *data, int id)
{
	sem_wait(sim->sim);
	if (!sim->end)
	{
		sem_wait(sim->print);
		printf(data, time_diff_ms(sim->start_time, time_now()), id + 1);
		sem_post(sim->print);
	}
	sem_post(sim->sim);
}

int	sim_end(t_sim *sim)
{
	sem_wait(sim->sim);
	if (sim->end)
	{
		sem_post(sim->sim);
		return (1);
	}
	sem_post(sim->sim);
	return (0);
}