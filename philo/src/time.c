/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:11:42 by hyko              #+#    #+#             */
/*   Updated: 2022/08/17 17:12:17 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_ms_time(void) //현재시간을 ms 단위로 반환
{
	struct timeval	time;
	unsigned long	ms_time;

	gettimeofday(&time, NULL);
	ms_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms_time);
}

//usleep은 인자로 받은 시간에 정확히 끝나는 것이 아니고, 
//최소 인자만큼은 보장을 해주는 것이라 정확한 시간 측정이 필요함
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

unsigned long	time_check(t_philo *philo) //현재시간 - 시작시간
{
	unsigned long	time_gap;

	time_gap = get_ms_time() - philo->game->start_time;
	return (time_gap);
}
