/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 09:26:23 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/07 12:37:45 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo)
{
	philo->count = 0;
	philo->must_eat_count = -1;
	philo->time_to_die = 0;
	philo->time_to_eat = 0;
	philo->time_to_sleep = 0;
	philo->philosophers = NULL;
}

void	parse_args(int ac, char **av, t_philo *philo)
{
	philo->count = atoi(av[1]);
	philo->time_to_die = atoi(av[2]);
	philo->time_to_eat = atoi(av[3]);
	philo->time_to_sleep = atoi(av[4]);
	if (ac > 5)
		philo->must_eat_count = atoi(av[5]);
}

int	main(int ac, char **av)
{
	t_philo	philo;

	if (ac < 5 || ac > 6)
	{
		print_usage();
		return (1);
	}
	init_philo(&philo);
	parse_args(ac, av, &philo);
	if (!alloc_philo(&philo))
        return (1);
	debug_philo(&philo);
    exit_philosophers(&philo);
	return (0);
}
