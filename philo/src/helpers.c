/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:22:03 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/29 15:56:37 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_usage(void)
{
	printf("usage: ./philo %s %s %s %s %s\n", NUM_PHILO, TIME_TO_DIE,
			TIME_TO_EAT, TIME_TO_SLEEP, MUST_EAT);
}

void	debug_sim(t_sim *sim)
{
	printf("sim->count=%d\n", sim->count);
	printf("sim->time_to_die=%d\n", sim->time_to_die);
	printf("sim->time_to_eat=%d\n", sim->time_to_eat);
	printf("sim->time_to_sleep=%d\n", sim->time_to_sleep);
	printf("sim->must_eat_count=%d\n", sim->must_eat_count);
}

void	debug_philo(t_philo *philo)
{
	printf("=========================\n");
	printf("id=%d\n", philo->id);
	printf("dead=%d\n", philo->dead);
	printf("eaten_count=%d\n", philo->eaten_count);
	printf("last_eat_at=%lld\n", philo->last_eat_at);
	printf("=========================\n");
}
