/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:02:48 by hyko              #+#    #+#             */
/*   Updated: 2022/08/09 19:55:33 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	death_check(t_philo	*philo) // 누군가 죽었는지? + 내가 죽었는지?
// {
// 	unsigned long	time_gap;
	
// 	pthread_mutex_lock(&philo->game->death_check_mutex);
// 	if (philo->game->death_flag != 0)
// 	{
// 		pthread_mutex_unlock(&philo->game->death_check_mutex);
// 		return (TRUE);
// 	}
	
// 	time_gap = get_ms_time() - philo->last_eat;
// 	if (time_gap >= philo->game->time_to_die) // 등호 확인 > or >=
// 	{
// 		philo->game->death_flag = philo->id;
// 		print_msg(philo, 'd');
// 		pthread_mutex_unlock(&philo->game->death_check_mutex);
// 		return (TRUE);
// 	}
// 	pthread_mutex_unlock(&philo->game->death_check_mutex);
// 	return (FALSE);
// }

unsigned long	time_check(t_philo *philo) //현재시간 - 시작시간
{
	unsigned long	time_gap;
	
	time_gap = get_ms_time() - philo->game->start_time;
	return (time_gap);
}

int	print_msg(t_philo *philo, char type)
{
	pthread_mutex_lock(&(philo->game->print));
	// if (death_check(philo) == TRUE && type != 'd')
	// 	return (-1);
	// else
	// {
	// 	if (type == 'f')
	// 		printf("%lu %d has taken a fork\n", time_check(philo), philo->id);
	// 	else if (type == 'e')
	// 		printf("%lu %d is eating\n", time_check(philo), philo->id);
	// 	else if (type == 's')
	// 		printf("%lu %d is sleeping\n", time_check(philo), philo->id);
	// 	else if (type == 't')
	// 		printf("%lu %d is thinking\n", time_check(philo), philo->id);
	// 	else if (type == 'd')
	// 		printf("%lu %d is died\n", time_check(philo), philo->id);
	// 	pthread_mutex_unlock(&(philo->game->print));
	// }
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
		if (philo->game->death_flag == 0)
			philo_sleep(philo);
		else
			break ;
		// if (philo_grab_fork(philo) < 0)
		// 	break ;
		// if (philo_eat(philo) < 0)
		// 	break ;
		// if (philo_sleep(philo) < 0)
		// 	break ;
	}
	return(philo);
}
