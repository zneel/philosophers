/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:14:08 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/30 09:48:51 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_to_ms(t_timeval time)
{
	return ((((long long)time.tv_sec) * 1000) + (time.tv_usec / 1000));
}

long long	time_now(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	return (time_to_ms(time));
}

long long	time_diff_ms(long long a, long long b)
{
	if (a > b)
		return (a - b);
	else
		return (b - a);
}

int	sleep_ms(long long ms)
{
	long long	start;

	start = time_now();
	while ((time_now() - start) < ms)
		usleep(ms * 1000);
	return (1);
}
