/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:22:40 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/08 19:28:12 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_routine(void *data)
{
	t_sim	*sim;
	t_philo	*philo;

	sim = ((t_philo *)data)->sim;
	philo = ((t_philo *)data);
	//printf("starting routine:\n");
	while (!is_dead(sim, philo) && sim->end == 0)
	{
		//debug_philo(philo);
		//debug_sim(sim);
		p_eat(sim, philo);
		p_think(sim, philo);
		p_sleep(sim, philo);
		p_dead(sim, philo);
	}
	return (NULL);
}
