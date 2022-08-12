/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:11:54 by hyko              #+#    #+#             */
/*   Updated: 2022/08/12 16:50:07 by hyko             ###   ########.fr       */
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
	// philo->last_eat = get_ms_time();
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