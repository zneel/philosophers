/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 00:54:33 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/02 01:29:19 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_forks(t_sim *sim)
{
	sim->forks = sem_open("forks", O_CREAT, 0644, sim->count);
	if (sim->forks == SEM_FAILED)
	{
		printf("Error: sem_open failed\n");
		return (0);
	}
	return (1);
}