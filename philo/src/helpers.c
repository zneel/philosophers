/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:22:03 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/07 12:22:32 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_usage(void)
{
	printf("usage: ./philo %s %s %s %s %s\n",
			NUM_PHILO,
			TIME_TO_DIE,
			TIME_TO_EAT,
			TIME_TO_SLEEP,
			MUST_EAT);
}
void	debug_philo(t_philo *philo)
{
	printf("philo->count=%d\n", philo->count);
	printf("philo->time_to_die=%d\n", philo->time_to_die);
	printf("philo->time_to_eat=%d\n", philo->time_to_eat);
	printf("philo->time_to_sleep=%d\n", philo->time_to_sleep);
	printf("philo->must_eat_count=%d\n", philo->must_eat_count);
}