/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:25:22 by hyko              #+#    #+#             */
/*   Updated: 2022/08/19 16:38:27 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_is_full(t_philo *philo)
{
	pthread_mutex_lock(&(philo->full_mutex));
	philo->is_full = 1;
	pthread_mutex_unlock(&(philo->full_mutex));
}

void	*philo_thread(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2 == 0)
		usleep(100);
	while (death_check(philo) == 0)
	{
		if (philo->eat_cnt == philo->must_eat)
			philo_is_full(philo);
		if (((death_check(philo) == 0) && philo_grab_fork(philo) == 0) == FALSE)
			break ;
		if ((death_check(philo) == 0 && philo->l_fork != philo->r_fork
				&& philo_eat(philo) == 0) == FALSE)
		{
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			break ;
		}
		if (((death_check(philo) == 0) && philo_sleep(philo) == 0) == FALSE)
			break ;
	}
	return (0);
}
