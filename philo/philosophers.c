#include "philosophers.h"

int struct_init(t_philo *philo)
{
	if(!philo)
		return 0;
	// philo
}

void	philosophy_start(t_params args)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if(!struct_init(philo))
		return ;
}
