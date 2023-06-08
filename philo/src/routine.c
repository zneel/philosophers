/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:22:40 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/08 13:53:37 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_routine(void *args)
{
	t_tphilo *philo;
	t_sim *sim;

	philo = ((t_args *)(args))->philo;
	sim = ((t_args *)(args))->sim;
	printf("starting routine:\n");
	printf("sim->end=%d\n", sim->end);
	printf("philo->id=%d\n", philo->id);
	while (!is_dead(sim, philo) && sim->end == 0)
	{
		p_eat(sim, philo);
		p_think(sim, philo);
		p_sleep(sim, philo);
		p_dead(sim, philo);
	}
	return (NULL);
}