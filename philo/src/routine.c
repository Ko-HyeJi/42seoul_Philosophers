/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:55:23 by hyko              #+#    #+#             */
/*   Updated: 2022/08/19 15:55:33 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_grab_fork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->l_fork) == 0 && death_check(philo) == 0)
		print_msg(philo, 'f');
	if (philo->l_fork != philo->r_fork
		&& pthread_mutex_lock(philo->r_fork) == 0 && death_check(philo) == 0)
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
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
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
