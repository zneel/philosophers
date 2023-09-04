/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:22:03 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/04 19:41:52 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_usage(void)
{
	printf("usage: ./philo %s %s %s %s %s\n", NUM_PHILO, TIME_TO_DIE,
		TIME_TO_EAT, TIME_TO_SLEEP, MUST_EAT);
}
