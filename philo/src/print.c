/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:40 by hyko              #+#    #+#             */
/*   Updated: 2022/08/19 17:18:08 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_msg(t_philo *philo, char type)
{
	pthread_mutex_lock(&(philo->game->print));
	if (death_check(philo) == 0)
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
	{
		pthread_mutex_unlock(&(philo->game->print));
		return (-1);
	}
	return (0);
}

int	print_error_msg(char *msg)
{
	printf("%s", msg);
	return (-1);
}
