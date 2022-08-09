/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:45:35 by hyko              #+#    #+#             */
/*   Updated: 2022/08/03 18:57:33 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
		if (str[i] == '\0')
			return (-1);
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}

long long	ft_atol(const char *str)
{
	long long	i;
	long long	sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

int	print_error_msg(char *msg)
{
	printf("%s", msg);
	return (-1);
}

unsigned long	get_ms_time(void) //현재시간을 ms 단위로 반환
{
	struct timeval	time;
	unsigned long ms_time;
	
	gettimeofday(&time, NULL);
	ms_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms_time);
}

//usleep은 인자로 받은 시간에 정확히 끝나는 것이 아니고, 
//최소 인자만큼은 보장을 해주는 것이라 정확한 시간 측정이 필요함
void	philo_alarm(unsigned long time)
{
	unsigned long sleep_time;
	unsigned long alarm_time;
	
	sleep_time = get_ms_time();
	alarm_time = sleep_time + time;
	while (sleep_time < alarm_time)
	{
		usleep(300);
		sleep_time = get_ms_time();
	}
}
