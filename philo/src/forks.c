/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:47:26 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/04 19:42:12 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_fork_mutex(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
		pthread_mutex_destroy(&forks[i++]);
}

int	alloc_forks(t_sim *sim)
{
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->count);
	if (!sim->forks)
		return (0);
	memset(sim->forks, 0, sizeof(pthread_mutex_t) * sim->count);
	return (1);
}

int	init_forks(t_sim *sim)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (i < sim->count)
	{
		err = pthread_mutex_init(&sim->forks[i], NULL);
		if (err)
		{
			printf("Error initializing mutex\n");
			break ;
		}
		i++;
	}
	if (err)
	{
		destroy_fork_mutex(sim->forks, i);
		free(sim->forks);
	}
	return (err == 0);
}
