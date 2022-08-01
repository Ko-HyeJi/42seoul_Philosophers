/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:38:13 by hyko              #+#    #+#             */
/*   Updated: 2022/08/01 15:36:20 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_game(t_game *game)
{
	printf("num_of_philo : %d\n", game->num_of_philo);
	printf("time_to_die : %d\n", game->time_to_die);
	printf("time_to_eat : %d\n", game->time_to_eat);
	printf("time_to_sleep : %d\n", game->time_to_sleep);
	printf("must_eat : %d\n", game->must_eat);
	printf("death_check : %d\n", game->death_check);
}

void	print_philo(t_game *game)
{
	int	i = 0;
	while (i < game->num_of_philo)
	{
		printf("num : %d\n", game->philo[i].num);
		printf("l_fork : %p\n", game->philo[i].left_fork);
		printf("r_fork : %p\n", game->philo[i].right_fork);
		printf("eat_cnt : %d\n", game->philo[i].eat_cnt);
		printf("death : %d\n\n", game->philo[i].death);
		i++;
	}
}

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
	if (argc == 6)
		game->must_eat = ft_atol(argv[5]);
	else
		game->must_eat = 0;
	if (game->num_of_philo < 0 || game->time_to_die < 0|| game->time_to_eat < 0 || game->time_to_sleep < 0 || game->must_eat < 0)
		return (-1);
	return (0);
}

int	malloc_struct(t_game *game)
{
	game->philo = malloc(sizeof(t_philo) * game->num_of_philo);
	if (game->philo == NULL)
		return (-1);
	game->fork = malloc(sizeof(pthread_mutex_t) * game->num_of_philo);
	printf("num of philo : %d\n", game->num_of_philo);
	if (game->fork == NULL)
		return (-1);
	return (0);
}

int	init_game(int argc, char **argv, t_game *game)
{	
	if (check_arg(argc, argv, game) < 0)
	{
		free (game);
		return (print_error_msg("error : invalid argument\n"));
	}
	if (malloc_struct(game) < 0)
		return (print_error_msg("error : malloc failed\n"));
	
	int	i = 0;
	printf("%p\n",(game->fork));
	while (i < game->num_of_philo)
	{
		pthread_mutex_init(&(game->fork[i]), NULL);
		// printf("i = %d, ptr : %p\n", i, &(game->fork[i]));
		i++;
	}
	gettimeofday(&game->start_time, NULL);
	printf("start_time : %ld\n", game->start_time);
	return (0);
}

void * philo_thread(void *philo)
{
	t_philo * p = (t_philo *)philo;
	
	return(0);
}

int	init_philo(t_game *game)
{
	int	i;
	t_philo	*philo; 

	philo = game->philo;
	i = 0;
	while (i < game->num_of_philo)
	{
		philo[i].num = i + 1;
		pthread_create(&(philo[i].thread), NULL, &(philo_thread), &(philo[i]));		//pthread_t, pthread_attr_t, 함수, 매개변수
		// 
		usleep(1000);
		philo[i].left_fork = &game->fork[i];
		if ((i + 1) == game->num_of_philo)
			philo[i].right_fork = &game->fork[0];
		else
			philo[i].right_fork = &game->fork[i + 1];
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game *game;
	int	i;
	game = malloc(sizeof(t_game));
	if (game == NULL)
		return (print_error_msg("error : malloc failed\n"));
	if (init_game(argc, argv, game) < 0)
		return (print_error_msg("error : game initialize failed\n"));
	// print_game(game);
	if (init_philo(game) < 0)
		return (print_error_msg("error : philo initialize failed\n"));
	// print_philo(game);
	i = 0;
	while (i < game->num_of_philo)
	{
		// printf("before join\n");
		pthread_join(game->philo[i].thread, NULL);
		// printf("%d, %d\n", i, game->philo[i].num);
		i++;
	}
	return (0);
}
