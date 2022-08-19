/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:11:42 by hyko              #+#    #+#             */
/*   Updated: 2022/08/19 17:00:53 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_ms_time(void)
{
	struct timeval	time;
	unsigned long	ms_time;

	gettimeofday(&time, NULL);
	ms_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms_time);
}

void	philo_alarm(unsigned long time)
{
	unsigned long	sleep_time;
	unsigned long	alarm_time;

	sleep_time = get_ms_time();
	alarm_time = sleep_time + time;
	while (sleep_time < alarm_time)
	{
		usleep(300);
		sleep_time = get_ms_time();
	}
}

unsigned long	time_check(t_philo *philo)
{
	unsigned long	time_gap;

	time_gap = get_ms_time() - philo->start_time;
	return (time_gap);
}
