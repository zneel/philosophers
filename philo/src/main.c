/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 09:26:23 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/23 10:14:39 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	is_int_range(char *av)
{
	if (ft_strlen(av) > 10)
		return (false);
	return (true);
}

t_bool	is_over_int_max(char *av)
{
	if (ft_atoll(av) > INT_MAX)
		return (true);
	return (false);
}

t_bool	parse_args(int ac, char **av, t_sim *sim)
{
	if (!is_int_range(av[1]) || !is_int_range(av[2]) || !is_int_range(av[3])
		|| !is_int_range(av[4]) || (ac > 5 && !is_int_range(av[5])))
		return (false);
	if (is_over_int_max(av[1]) || is_over_int_max(av[2])
		|| is_over_int_max(av[3]) || is_over_int_max(av[4]) || (ac > 5
			&& is_over_int_max(av[5])))
		return (false);
	sim->count = ft_atoll(av[1]);
	sim->time_to_die = ft_atoll(av[2]);
	sim->time_to_eat = ft_atoll(av[3]);
	sim->time_to_sleep = ft_atoll(av[4]);
	sim->must_eat_count = -1;
	if (ac > 5)
		sim->must_eat_count = ft_atoll(av[5]);
	if ((sim->count < 1 || sim->count > 200) || sim->time_to_die < 60
		|| sim->time_to_eat < 60 || sim->time_to_sleep < 60 || (ac > 5
			&& sim->must_eat_count < 1))
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	t_sim	sim;

	if (ac < 5 || ac > 6)
		return (print_usage(), 1);
	if (!parse_args(ac, av, &sim))
		return (print_usage(), 1);
	simulate(&sim);
	return (0);
}
