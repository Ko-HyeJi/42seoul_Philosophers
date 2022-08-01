/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:08:49 by hyko              #+#    #+#             */
/*   Updated: 2022/07/30 22:29:49 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h> //memset
# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <unistd.h> //write, usleep
# include <sys/time.h> //gettimeofday
# include <pthread.h> //pthread_*
#include <stdio.h> //제출전에 지우기!!!!!

typedef struct s_philo
{
	int				num;
	pthread_t		thread;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	int	eat_cnt;
	int	death;
}	t_philo;

typedef struct s_game
{
	t_philo	*philo;
	pthread_mutex_t *fork;
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
	int	death_check;
}	t_game;

/* philo_utils.c */
int	is_num(char *str);
long long	ft_atol(const char *str);
int	print_error_msg(char *msg);

#endif