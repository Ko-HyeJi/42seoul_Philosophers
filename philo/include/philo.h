/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:08:49 by hyko              #+#    #+#             */
/*   Updated: 2022/08/20 16:37:56 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <unistd.h> //write, usleep
# include <sys/time.h> //gettimeofday
# include <pthread.h> //pthread_*

typedef struct s_game
{
	int				num_of_philo;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				must_eat;
	unsigned long	start_time;
	int				death_flag;
	pthread_t		monitoring;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
}	t_game;

typedef struct s_philo
{
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				must_eat;
	unsigned long	start_time;
	t_game			*game;
	int				id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				eat_cnt;
	unsigned long	last_eat;
	int				is_full;
	pthread_t		thread;
	pthread_mutex_t	full_mutex;
	pthread_mutex_t	last_eat_mutex;

}	t_philo;

/* initialize.c */
int				init_game(int argc, char **argv, t_game *game);
int				init_philo(t_game *game, t_philo *philo);

/* monitoring_thread.c */
void			*monitoring_thread(void *param);

/* philo_thread.c */
void			*philo_thread(void *param);

/* print.c */
int				print_msg(t_philo *philo, char type);
int				print_error_msg(char *msg);

/* routine.c */
int				philo_grab_fork(t_philo *philo);
int				philo_eat(t_philo *philo);
int				philo_sleep(t_philo *philo);

/* time.c */
unsigned long	get_ms_time(void);
unsigned long	time_check(t_philo *philo);
void			philo_alarm(unsigned long time);

/* utils.c */
int				is_num(char *str);
long long		ft_atol(const char *str);
int				death_check(t_philo *philo);

# define TRUE 1
# define FALSE 0

#endif