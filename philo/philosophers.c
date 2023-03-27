#include "philosophers.h"

void *print_tree(void *a)
{

}

void	philosophy_start(t_params args)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return ;
	philo->philos = ft_calloc(args.nb_philos, sizeof(pthread_t));
	if (!philo->philos)
		return;
}
