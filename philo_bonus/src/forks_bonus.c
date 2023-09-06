/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:47:26 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/06 13:23:30 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	init_forks(t_sim *sim)
{
	sim->s_forks = sem_open("forks", O_CREAT, 0644, sim->count);
	if (sim->s_forks == SEM_FAILED)
	{
		printf("Error creating semaphore\n");
		return (false);
	}
	return (true);
}