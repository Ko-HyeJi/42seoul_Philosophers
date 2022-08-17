/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:40 by hyko              #+#    #+#             */
/*   Updated: 2022/08/17 17:13:08 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error_msg(char *msg)
{
	printf("%s", msg);
	return (-1);
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
