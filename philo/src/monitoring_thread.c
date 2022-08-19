/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_thread.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:25:48 by hyko              #+#    #+#             */
/*   Updated: 2022/08/19 16:58:04 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_dead_philo(t_philo *philo)
{
	pthread_mutex_lock(&(philo->last_eat_mutex));
	if (get_ms_time() - philo->last_eat
		>= philo->game->time_to_die)
	{
		pthread_mutex_unlock(&(philo->last_eat_mutex));
		pthread_mutex_lock(&(philo->game->death));
		philo->game->death_flag = 1;
		pthread_mutex_unlock(&(philo->game->death));
		print_msg(philo, 'd');
		return (TRUE);
	}
	pthread_mutex_unlock(&(philo->last_eat_mutex));
	return (FALSE);
}

static int	check_full_philo(t_philo *philo)
{
	pthread_mutex_lock(&(philo->full_mutex));
	if (philo->is_full == TRUE)
	{
		pthread_mutex_unlock(&(philo->full_mutex));
		return (TRUE);
	}
	pthread_mutex_unlock(&(philo->full_mutex));
	return (FALSE);
}

static void	philos_are_full(t_philo *philo)
{
	pthread_mutex_lock(&(philo->game->death));
	printf("All the philos are full\n");
	philo->game->death_flag = 1;
	pthread_mutex_unlock(&(philo->game->death));
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
			if (check_dead_philo(&philo[i]) == TRUE)
				break ;
			num_of_full_philo += check_full_philo(&philo[i]);
			i++;
		}
		if (num_of_full_philo == philo->game->num_of_philo)
		{
			philos_are_full(philo);
			break ;
		}
	}
	return (0);
}
