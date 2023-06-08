/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 09:26:23 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/08 14:18:47 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_args(int ac, char **av, t_sim *sim)
{
	sim->count = atoi(av[1]);
	sim->time_to_die = atoi(av[2]);
	sim->time_to_eat = atoi(av[3]);
	sim->time_to_sleep = atoi(av[4]);
	if (ac > 5)
		sim->must_eat_count = atoi(av[5]);
}

int	main(int ac, char **av)
{
	t_sim	sim;
    int err;

	if (ac < 5 || ac > 6)
	{
		print_usage();
		return (1);
	}
	init_simulation(&sim);
	parse_args(ac, av, &sim);
    err = simulate(&sim);
    printf("err=%d\n", err);
	return (0);
}
