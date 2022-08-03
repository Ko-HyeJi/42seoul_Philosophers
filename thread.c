/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:02:48 by hyko              #+#    #+#             */
/*   Updated: 2022/08/03 15:44:58 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	time_check(t_philo *philo) //현재시간 - 시작시간
{
	unsigned long	time_gap;
	
	time_gap = get_ms_time() - philo->game->start_time;
	// printf("1. %lu\n", get_ms_time());
	// printf("2. %lu\n", philo->game->start_time);
	return (time_gap);
}

int	death_check(t_philo	*philo) // 누군가 죽었는지? + 내가 죽었는지?
{
	unsigned long	time_gap;
	
	if (philo->game->death_flag != 0)
		return (TRUE);
	
	time_gap = get_ms_time() - philo->last_eat;
	if (time_gap > philo->game->time_to_die)
	{
		philo->game->death_flag = philo->num;
		print_msg(philo, 'd');
		return (TRUE);
	}
	return (FALSE);
}

int	print_msg(t_philo *philo, char type)
{
	pthread_mutex_lock(&(philo->game->print));
	if (death_check(philo) == TRUE && type != 'd')
		return (-1);
	else
	{
		if (type == 'f')
			printf("%lu %d has taken a fork\n", time_check(philo), philo->num);
		else if (type == 'e')
			printf("%lu %d is eating\n", time_check(philo), philo->num);
		else if (type == 's')
			printf("%lu %d is sleeping\n", time_check(philo), philo->num);
		else if (type == 't')
			printf("%lu %d is thinking\n", time_check(philo), philo->num);
		else if (type == 'd')
			printf("%lu %d is died\n", time_check(philo), philo->num);
		pthread_mutex_unlock(&(philo->game->print));
	}
	return (0);
}


int	philo_grab_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork); //left_fork
	if (death_check(philo) == TRUE)
		return (-1);
	print_msg(philo, 'f');
	pthread_mutex_lock(philo->right_fork); //right_fork
	if (death_check(philo) == TRUE)
		return (-1);
	print_msg(philo, 'f');
	return (0);
}

int	philo_eat(t_philo *philo)
{
	print_msg(philo, 'e');
	philo->eat_cnt++;
	if (death_check(philo) == TRUE)
		return (-1);
	usleep(philo->game->time_to_eat * 1000);
	philo->last_eat = get_ms_time();
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (death_check(philo) == TRUE)
		return (-1);	
	print_msg(philo, 's');
	usleep(philo->game->time_to_sleep * 1000);
	if (death_check(philo) == TRUE)
		return (-1);
	print_msg(philo, 't');
	return (0);
}

void * philo_thread(void *param) //매개변수를 void*로 받아서 t_philo*로 캐스팅 해줘야 함
{
	t_philo *philo = (t_philo *)param;

	if (philo->num % 2 == 1) //홀수번 필로 대기
		usleep(10);
	while (philo->eat_cnt != philo->game->must_eat && philo->game->death_flag == 0)
	{
		if (philo_grab_fork(philo) < 0)
			break ;
		if (philo_eat(philo) < 0)
			break ;
		if (philo_sleep(philo) < 0)
			break ;
	}
	return(philo);
}