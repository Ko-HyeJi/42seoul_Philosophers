/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:08:49 by hyko              #+#    #+#             */
/*   Updated: 2022/08/03 19:23:39 by hyko             ###   ########.fr       */
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
	// t_philo	*philo;
	pthread_mutex_t *fork;
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
	int	death_flag;
	pthread_mutex_t death_mutex;
	// struct timeval	start_time;
	unsigned long	start_time;
	pthread_mutex_t print;
}	t_game;

typedef struct s_philo
{
	t_game			*game;
	int				num;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int	eat_cnt;
	unsigned long	last_eat;
	// int	is_dead; -> game구조체 death_check 값을 죽은 필로 번호로?
	// struct timeval	start_time;
}	t_philo;

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

/* thread.c */
unsigned long	time_check(t_philo *philo);
int	death_check(t_philo	*philo);
int	print_msg(t_philo *philo, char type);
int	philo_grab_fork(t_philo *philo);
int	philo_eat(t_philo *philo);
int	philo_sleep(t_philo *philo);
void * philo_thread(void *param);

/* tmp -> 지워야함!!! */
void	print_game(t_game *game);
void	print_philo(t_game *game, t_philo *philo);

#define	TRUE 1
#define	FALSE 0

#endif