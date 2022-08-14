/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:38:13 by hyko              #+#    #+#             */
/*   Updated: 2022/08/15 02:28:27 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_game *game;
	t_philo	*philo;
	int	i;

	game = malloc(sizeof(t_game));
	if (game == NULL)
		return (print_error_msg("error : memory allocation failed\n"));
	if (init_game(argc, argv, game) < 0)
		return (print_error_msg("error : game initialization failed\n"));
	philo = malloc(sizeof(t_philo) * game->num_of_philo);
	if (philo == NULL)
		return (print_error_msg("error : memory allocation failed\n"));
	if (init_philo(game, philo) < 0)
		return (print_error_msg("error : philo initialization failed\n"));
	pthread_create(&(game->monitoring), NULL, &(monitoring_thread), &(philo[0]));
	pthread_join(game->monitoring, NULL);
	free(game->fork);
	free(game);
	free(philo);
	// system("leaks philo");
	return (0);
}
