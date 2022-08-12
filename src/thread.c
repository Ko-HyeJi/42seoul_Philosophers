/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:02:48 by hyko              #+#    #+#             */
/*   Updated: 2022/08/12 23:20:28 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	time_check(t_philo *philo) //현재시간 - 시작시간
{
	unsigned long	time_gap;
	
	time_gap = get_ms_time() - philo->game->start_time;
	return (time_gap);
}

int	print_msg(t_philo *philo, char type)
{
	pthread_mutex_lock(&(philo->game->print));
	if (philo->game->death_flag == 0)
	{
		if (type == 'f')
			printf("%lu %d has taken a fork\n", time_check(philo), philo->id);
		else if (type == 'e')
			printf("%lu %d is eating\n", time_check(philo), philo->id);
		else if (type == 's')
			printf("%lu %d is sleeping\n", time_check(philo), philo->id);
		else if (type == 't')
			printf("%lu %d is thinking\n", time_check(philo), philo->id);
		pthread_mutex_unlock(&(philo->game->print));		
	}
	else if (type == 'd')
	{
		printf("%lu %d is died\n", time_check(philo), philo->id);
		pthread_mutex_unlock(&(philo->game->print));		
	}
	else
		return (-1);
	return (0);
}

void *philo_thread(void *param) //매개변수를 void*로 받아서 t_philo*로 캐스팅 해줘야 함
{
	t_philo *philo = (t_philo *)param;

	if (philo->id % 2 == 1)
		usleep(100);
		
	while (philo->eat_cnt != philo->game->must_eat) // && philo->game->death_flag == 0)
	{
		if (philo->game->death_flag == 0)
			philo_grab_fork(philo);
		else
			break ;
		if (philo->game->death_flag == 0)
			philo_eat(philo);
		else
			break ;
		if (philo->game->death_flag == 0 && philo->eat_cnt != philo->game->must_eat)
			philo_sleep(philo);
		else
			break ;
	}
	// if (philo->game->must_eat == philo->eat_cnt)
	// 	printf("philo eat done!!!\n");
	return (philo);
}

void	*monitoring_thread(void *param)
{
	t_philo *philo = (t_philo *)param;
	int	i;

	while (philo->game->death_flag == 0)
	{
		i = 0;
		while (i < philo->game->num_of_philo)
		{
			if (get_ms_time() - philo[i].last_eat >= philo->game->time_to_die)
			{
				philo->game->death_flag = i + 1;
				print_msg(&philo[i], 'd');
				break ;
			}
			i++;
		}
		usleep(100); // 0.1ms
	}
	return (0);
}
