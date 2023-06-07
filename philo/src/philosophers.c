/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:21:39 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/07 12:22:45 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_philosophers(t_philo *philo, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(philo->philosophers[i++]);
	free(philo->philosophers);
}

int	alloc_philo(t_philo *philo)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	philo->philosophers = malloc(sizeof(t_tphilo *) * philo->count);
	if (!philo->philosophers)
		return (0);
	while (i < philo->count)
	{
		philo->philosophers[i] = malloc(sizeof(t_tphilo));
		if (!philo->philosophers[i])
		{
			err = 1;
			break ;
		}
		i++;
	}
	if (err)
	{
		destroy_philosophers(philo, i);
		return (0);
	}
	return (1);
}