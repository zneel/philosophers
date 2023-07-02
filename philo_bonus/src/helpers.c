/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 00:53:47 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/02 01:27:29 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_usage(void)
{
	printf("usage: ./philo %s %s %s %s %s\n", NUM_PHILO, TIME_TO_DIE,
			TIME_TO_EAT, TIME_TO_SLEEP, MUST_EAT);
}