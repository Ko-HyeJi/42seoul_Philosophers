/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:02:48 by hyko              #+#    #+#             */
/*   Updated: 2022/08/17 17:13:29 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_grab_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork); //left_fork
	if (philo->game->death_flag == 0)
		print_msg(philo, 'f');
	pthread_mutex_lock(philo->right_fork); //right_fork
	if (philo->game->death_flag == 0)
		print_msg(philo, 'f');
	return (0);
}

int	philo_eat(t_philo *philo)
{
	if (philo->game->death_flag == 0)
		print_msg(philo, 'e');
	philo->last_eat = get_ms_time();
	philo->eat_cnt++;
	philo_alarm(philo->game->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (philo->game->death_flag == 0)
		print_msg(philo, 's');
	philo_alarm(philo->game->time_to_sleep);
	if (philo->game->death_flag == 0)
		print_msg(philo, 't');
	return (0);
}

void *philo_thread(void *param) //매개변수를 void*로 받아서 t_philo*로 캐스팅 해줘야 함
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2 == 0)
		usleep(100);
	while (philo->eat_cnt != philo->game->must_eat)
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
	}
	philo->game->eat_flag++;
	pthread_detach(philo->thread);
	return (philo);
}

void	*monitoring_thread(void *param)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)param;
	while (philo->game->death_flag == 0)
	{
		if (philo->game->eat_flag == philo->game->num_of_philo)
		{
			printf("All philosophers ate it all\n");
			break ;
		}
		i = 0;
		while (i < philo->game->num_of_philo)
		{
			if (philo[i].game->must_eat == philo[i].eat_cnt)
			{
				i++;
			}
			else if (get_ms_time() - philo[i].last_eat >= philo->game->time_to_die)
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
