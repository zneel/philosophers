/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:44:53 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/02 01:29:44 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	parse_args(int ac, char **av, t_sim *sim)
{
	sim->count = ft_atoi(av[1]);
	sim->time_to_die = ft_atoi(av[2]);
	sim->time_to_eat = ft_atoi(av[3]);
	sim->time_to_sleep = ft_atoi(av[4]);
	sim->must_eat_count = -1;
	if (ac > 5)
		sim->must_eat_count = ft_atoi(av[5]);
	if ((sim->count < 1 || sim->count > 200) || sim->time_to_die < 60
		|| sim->time_to_eat < 60 || sim->time_to_sleep < 60 || (ac > 5
			&& sim->must_eat_count < 1))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_sim sim;

	if (ac < 5 || ac > 6)
		return (print_usage(), 1);
	if (!parse_args(ac, av, &sim))
		return (print_usage(), 1);
	simulate(&sim);
	return (0);
}