/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:38:13 by hyko              #+#    #+#             */
/*   Updated: 2022/08/18 19:55:55 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_game	game;
	t_philo	*philo;
	int		i;

	if (argc < 5 || argc > 6)
		return (-1);
	if (init_game(argc, argv, &game) < 0)
		return (print_error_msg("error : game initialization failed\n"));
	philo = malloc(sizeof(t_philo) * game.num_of_philo);
	if (philo == NULL)
		return (print_error_msg("error : memory allocation failed\n"));
	if (init_philo(&game, philo) < 0)
		return (print_error_msg("error : philo initialization failed\n"));
	pthread_create(&(game.monitoring), NULL, &(monitoring_thread), philo);
	pthread_join(game.monitoring, NULL);
	i = 0;
	while (i < game.num_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	free(game.fork);
	free(philo);
	// system("leaks philo"); 
	return (0);
}
