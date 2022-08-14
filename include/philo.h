/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:08:49 by hyko              #+#    #+#             */
/*   Updated: 2022/08/14 09:04:39 by hyko             ###   ########.fr       */
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


typedef struct s_game
{
	unsigned long	start_time;
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
	int	death_flag;
	int	eat_flag;
	pthread_t	monitoring;
	pthread_mutex_t *fork;
	pthread_mutex_t print;
}	t_game;


typedef struct s_philo
{
	t_game			*game;
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int	eat_cnt;
	unsigned long	last_eat;
}	t_philo;

// typedef struct s_monitor
// {
// 	t_philo	*philo;
// 	t_game	*game;
// 	pthread_t	thread;
// }	t_monitor;

/* main.c */
void * philo_thread(void *philo);

/* philo_utils.c */
int	is_num(char *str);
long long	ft_atol(const char *str);
int	print_error_msg(char *msg);
unsigned long	get_ms_time(void);
void	philo_alarm(unsigned long time);

/* initialize.c */
int	check_arg(int argc, char **argv, t_game *game);
int	malloc_struct(t_game *game);
int	init_game(int argc, char **argv, t_game *game);
// int	init_philo(t_game *game);
int	init_philo(t_game *game, t_philo *philo);
void	*monitoring_thread(void *param);

/* thread.c */
unsigned long	time_check(t_philo *philo);
// int	death_check(t_philo	*philo);
int	print_msg(t_philo *philo, char type);
void * philo_thread(void *param);

/* routine.c */
int	philo_grab_fork(t_philo *philo);
int	philo_eat(t_philo *philo);
int	philo_sleep(t_philo *philo);

/* tmp -> 지워야함!!! */
void	print_game(t_game *game);
void	print_philo(t_game *game, t_philo *philo);

#define	TRUE 1
#define	FALSE 0

#endif