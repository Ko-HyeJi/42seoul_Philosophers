/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:38:13 by hyko              #+#    #+#             */
/*   Updated: 2022/08/03 15:01:39 by hyko             ###   ########.fr       */
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
		return (print_error_msg("error : malloc failed\n"));
	
	if (init_game(argc, argv, game) < 0)
		return (print_error_msg("error : game initialize failed\n"));
	// print_game(game);
	philo = malloc(sizeof(t_philo) * game->num_of_philo);
	if (game == NULL)
		return (print_error_msg("error : malloc failed\n"));
	if (init_philo(game, philo) < 0)
		return (print_error_msg("error : philo initialize failed\n"));
	
	free(game->fork);
	
	// print_philo(game, philo);
	// i = 0;
	// while (i < game->num_of_philo)
	// {
	// 	pthread_join(philo[i].thread, NULL);
	// 	i++;
	// }
	return (0);
}
