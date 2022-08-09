/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:38:13 by hyko              #+#    #+#             */
/*   Updated: 2022/08/09 19:23:10 by hyko             ###   ########.fr       */
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
	// print_game(game);
	philo = malloc(sizeof(t_philo) * game->num_of_philo);
	if (game == NULL)
		return (print_error_msg("error : memory allocation failed\n"));
	if (init_philo(game, philo) < 0)
		return (print_error_msg("error : philo initialization failed\n"));
	
	// if (init_monitor(game, philo, monitor) < 0)
	// 	return (print_error_msg("error : monitor initialization failed\n"));

	
	//////////////////////////
	// 필로가 한명인 경우 예외처리 //
	//////////////////////////

	free(game->fork);
	free(game);
	
	// print_philo(game, philo);
	// i = 0;
	// while (i < game->num_of_philo)
	// {
	// 	pthread_join(philo[i].thread, NULL);
	// 	i++;
	// }
	return (0);
}
