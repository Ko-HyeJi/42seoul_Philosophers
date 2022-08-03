/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:21:26 by hyko              #+#    #+#             */
/*   Updated: 2022/08/03 13:41:37 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(int argc, char **argv, t_game *game)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (-1);
	i = 1;
	while (argv[i])
	{
		if (is_num(argv[i]) < 0)
			return (-1);
		i++;
	}
	game->num_of_philo = ft_atol(argv[1]);
	game->time_to_die = ft_atol(argv[2]);
	game->time_to_eat = ft_atol(argv[3]);
	game->time_to_sleep = ft_atol(argv[4]);
	if (game->num_of_philo < 0 || game->time_to_die < 0|| game->time_to_eat < 0 || game->time_to_sleep < 0)
		return (-1);
	if (argc == 6)
    {
		game->must_eat = ft_atol(argv[5]);
        if (game->must_eat < 0)
            return (-1);
    }
    else
		game->must_eat = -1;
	return (0);
}

int	malloc_struct(t_game *game)
{
	// game->philo = malloc(sizeof(t_philo) * game->num_of_philo);
	// if (game->philo == NULL)
	// 	return (-1);
	game->fork = malloc(sizeof(pthread_mutex_t) * game->num_of_philo);
	if (game->fork == NULL)
		return (-1);
	return (0);
}

int	init_game(int argc, char **argv, t_game *game)
{	
	struct timeval	time_stamp;
	
	if (check_arg(argc, argv, game) < 0)
	{
		free (game);
		return (print_error_msg("error : invalid argument\n"));
	}
	if (malloc_struct(game) < 0)
		return (print_error_msg("error : malloc failed\n"));
	
	int	i = 0;
	while (i < game->num_of_philo)
	{
		pthread_mutex_init(&(game->fork[i]), NULL);
		i++;
	}
	gettimeofday(&time_stamp, NULL);
	game->start_time = get_ms_time(time_stamp);
    pthread_mutex_init(&game->print, NULL);
	return (0);
}

int	init_philo(t_game *game, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < game->num_of_philo)
	{
		philo[i].num = i + 1;
		philo[i].left_fork = &game->fork[i];
		if ((i + 1) == game->num_of_philo)
			philo[i].right_fork = &game->fork[0];
		else
			philo[i].right_fork = &game->fork[i + 1];
        philo[i].game = game;
        philo[i].last_eat = game->start_time;
		pthread_create(&(philo[i].thread), NULL, &(philo_thread), &(philo[i]));		//pthread_t, pthread_attr_t, 함수, 매개변수
		usleep(10);
		i++;
	}
	return (0);
}
