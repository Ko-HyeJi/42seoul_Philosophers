#include "philo.h"

void	print_game(t_game *game)
{
	printf("num_of_philo : %d\n", game->num_of_philo);
	printf("time_to_die : %d\n", game->time_to_die);
	printf("time_to_eat : %d\n", game->time_to_eat);
	printf("time_to_sleep : %d\n", game->time_to_sleep);
	printf("must_eat : %d\n", game->must_eat);
	printf("death_check : %d\n", game->death_check);
	// printf("start_time : %d\n", game->start_time.tv_usec);
	printf("\n");
}

void	print_philo(t_game *game, t_philo *philo)
{
	int	i = 0;
	while (i < game->num_of_philo)
	{
		printf("num : %d\n", philo[i].num);
		printf("l_fork : %p\n", philo[i].left_fork);
		printf("r_fork : %p\n", philo[i].right_fork);
		printf("eat_cnt : %d\n", philo[i].eat_cnt);
		// printf("is_dead : %d\n\n", philo[i].is_dead);
		// printf("start_time : %d\n", philo[i].game->start_time.tv_usec);
		i++;
	}
}