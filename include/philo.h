/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:08:49 by hyko              #+#    #+#             */
/*   Updated: 2022/08/17 17:18:14 by hyko             ###   ########.fr       */
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

typedef struct s_game
{
	unsigned long	start_time;
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				death_flag;
	int				eat_flag;
	pthread_t		monitoring;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
}	t_game;

typedef struct s_philo
{
	t_game			*game;
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				eat_cnt;
	unsigned long	last_eat;
}	t_philo;

/* philo_utils.c */
int				is_num(char *str);
long long		ft_atol(const char *str);

/* initialize.c */
int				check_arg(int argc, char **argv, t_game *game);
int				init_game(int argc, char **argv, t_game *game);
int				init_philo(t_game *game, t_philo *philo);

/* thread.c */
int				philo_grab_fork(t_philo *philo);
int				philo_eat(t_philo *philo);
int				philo_sleep(t_philo *philo);
void			*philo_thread(void *param);
void			*monitoring_thread(void *param);

/* print.c */
int				print_error_msg(char *msg);
int				print_msg(t_philo *philo, char type);

/* time.c */
unsigned long	get_ms_time(void);
void			philo_alarm(unsigned long time);
unsigned long	time_check(t_philo *philo);

# define	TRUE 1
# define	FALSE 0

#endif