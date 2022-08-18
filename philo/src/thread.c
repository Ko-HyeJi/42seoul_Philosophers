/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:02:48 by hyko              #+#    #+#             */
/*   Updated: 2022/08/18 20:03:05 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_check(t_philo *philo)
{
	pthread_mutex_lock(&(philo->game->death));
	if (philo->game->death_flag == 0)
	{
		pthread_mutex_unlock(&(philo->game->death));
		return (0);
	}
	pthread_mutex_unlock(&(philo->game->death));
	return (-1);
}

int	philo_grab_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (death_check(philo) == 0)
		print_msg(philo, 'f');
	pthread_mutex_lock(philo->right_fork);
	if (death_check(philo) == 0)
		print_msg(philo, 'f');
	return (0);
}

int	philo_eat(t_philo *philo)
{
	if (death_check(philo) == 0)
		print_msg(philo, 'e');
	{
		pthread_mutex_lock(&(philo->last_eat_mutex));
		philo->last_eat = get_ms_time();
		pthread_mutex_unlock(&(philo->last_eat_mutex));
	}
	philo->eat_cnt++;
	philo_alarm(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (death_check(philo) == 0)
		print_msg(philo, 's');
	philo_alarm(philo->time_to_sleep);
	if (death_check(philo) == 0)
		print_msg(philo, 't');
	return (0);
}

void	*philo_thread(void *param) //매개변수를 void*로 받아서 t_philo*로 캐스팅 해줘야 함
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2 == 0)
		usleep(100);
	while (death_check(philo) == 0)
	{
		if (philo->eat_cnt == philo->must_eat && philo->is_full == 0)
		{
			pthread_mutex_lock(&(philo->full_mutex));
			philo->is_full = 1;
			pthread_mutex_unlock(&(philo->full_mutex));
		}
		if (death_check(philo) == 0)
			philo_grab_fork(philo);
		else
			break ;
		if (death_check(philo) == 0)
			philo_eat(philo);
		else
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		if (death_check(philo) == 0)
			philo_sleep(philo);
		else
			break ;
		// if (((death_check(philo) == 0) && philo_sleep(philo) == 0) == 0)
		// 	break ;
	}
	return (0);
}

void	*monitoring_thread(void *param)
{
	t_philo	*philo;
	int		i;
	int		num_of_full_philo;

	philo = (t_philo *)param;
	while (death_check(philo) == 0)
	{
		i = 0;
		num_of_full_philo = 0;
		while (i < philo->game->num_of_philo)
		{
			pthread_mutex_lock(&(philo[i].last_eat_mutex));
			if (get_ms_time() - philo[i].last_eat
				>= philo->game->time_to_die)
			{
				pthread_mutex_unlock(&(philo[i].last_eat_mutex));
				pthread_mutex_lock(&(philo->game->death));
				philo->game->death_flag = 1;
				pthread_mutex_unlock(&(philo->game->death));
				print_msg(&philo[i], 'd');
				break ;
			}
			pthread_mutex_unlock(&(philo[i].last_eat_mutex));
			{
				pthread_mutex_lock(&(philo[i].full_mutex));
				num_of_full_philo += philo[i].is_full;
				pthread_mutex_unlock(&(philo[i].full_mutex));
			}
			i++;
		}
		if (num_of_full_philo == philo->game->num_of_philo)
		{
			pthread_mutex_lock(&(philo->game->death));
			philo->game->death_flag = 1;
			pthread_mutex_unlock(&(philo->game->death));
			break ;
		}
	}
	return (0);
}
