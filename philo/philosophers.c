#include "philosophers.h"
void philo_take_fork(t_philo	*philo)
{
	printf("%lld %d has taken a fork\n",  get_time_in_ms((struct timeval){0, 0}, 0) - get_time_in_ms(philo->start_time, 1),philo->id);
	pthread_mutex_lock(philo->right_fork);
	printf("%lld %d has taken a fork\n" , get_time_in_ms((struct timeval){0, 0}, 0) - get_time_in_ms(philo->start_time, 1),philo->id);
	pthread_mutex_lock(philo->left_fork);
}

long long get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_usleep(long long time)
{
	long long start;

	start = get_time();
	while (get_time() - start < time)
		usleep(500);
}

void philo_eat(t_philo *philo)
{
		if(philo->right_fork == NULL || philo->left_fork == NULL)
			return ;
		philo_take_fork(philo);
		printf("%lld %d is eating\n", get_time_in_ms((struct timeval){0, 0}, 0) - get_time_in_ms(philo->start_time, 1), philo->id);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(philo->meal);
		gettimeofday(&philo->last_meal, NULL);
		pthread_mutex_unlock(philo->meal);
		pthread_mutex_lock(philo->eat_count);
		philo->eat_counter++;
		pthread_mutex_unlock(philo->eat_count);
		ft_usleep(philo->params.time_to_eat);
}

void philo_sleep(t_philo *philo)
{
	printf("%lld %d is sleeping\n", get_time_in_ms((struct timeval){0, 0}, 0) - get_time_in_ms(philo->start_time, 1), philo->id);
	ft_usleep(philo->params.time_to_sleep);
}

void philo_think(t_philo *philo)
{
	printf("%lld %d is thinking\n", get_time_in_ms((struct timeval){0, 0}, 0) - get_time_in_ms(philo->start_time, 1), philo->id);
	ft_usleep(200);
}

long long get_diff_time(struct timeval start, struct timeval end)
{
	return ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000);
}

struct timeval get_time_of_day(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv);
}

int check_death(t_philos_table *table)
{
	int i;
	struct timeval time;
	FILE *fp;

	fp = fopen("log.txt", "a");
	i = -1;
	gettimeofday(&time, NULL);
	while (++i < table->params.nb_philos)
	{
		fprintf(fp, "id->%d\t%lld\n",table->philos[i]->id, get_time_in_ms((struct timeval){0, 0}, 0)\
		- get_time_in_ms(table->philos[i]->last_meal, 1));
		if (get_time_in_ms((struct timeval){0, 0}, 0) - get_time_in_ms(table->philos[i]->last_meal, 1) > table->params.time_to_die)
		{
			printf("\033[0;31m%lld %d died\n", get_time_in_ms((struct timeval){0, 0}, 0) - get_time_in_ms(table->philos[i]->start_time, 1),\
			table->philos[i]->id);
			return (1);
		}
	}
	fclose(fp);
	return (0);
}

int  philo_checker(void *ptr)
{
	int i;
	t_philo_checker *checker;

	checker  = (t_philo_checker *)ptr;
	ft_usleep(checker->table->params.nb_philos * 250);
	i = -1;
	while (++i < checker->table->params.nb_philos)	
	{
	    if(check_death(checker->table) && checker->table->philos[i]->last_meal.tv_sec > 0)
	    {
	        pthread_mutex_lock(checker->table->philos[i]->stat);
	        *checker->table->philos[i]->died_ptr = 1;
	        pthread_mutex_unlock(checker->table->philos[i]->stat);
	        return (0);
	    }		
	}
	return (1);
}

void *philosophers_routine(void *param)
{
	t_philo		*philo;
	int cond;

	philo = (t_philo *)param;
	if((philo->id & 1))
		ft_usleep(250);
	while(1)
	{
		pthread_mutex_lock(philo->stat);
		// cond = (*philo->died || !philo->right_fork || !philo->left_fork);
		cond = *philo->died_ptr;
		pthread_mutex_unlock(philo->stat);
		if (cond)
			return (NULL);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void init_checker_struct(t_philos_table *table, t_philo_checker **checker)
{
	*checker = malloc(sizeof(t_philo_checker));
	if (!checker)
		return ;
	(*checker)->death = malloc(sizeof(pthread_mutex_t));
	if (!(*checker)->death)
		return ;
	pthread_mutex_init((*checker)->death, NULL);
	(*checker)->table = table;
}

void philosophy_start(t_philos_table *table)
{
	int			i;
	t_philo		**philos;
	t_philo_checker *checker;

	i = -1;
	gettimeofday(&table->start_time, NULL);
	philos = table->philos;
	init_checker_struct(table, &checker);
	while (++i < table->params.nb_philos)
		pthread_create(&philos[i]->philo, NULL, philosophers_routine, philos[i]);
	i = -1;
	while(philo_checker(checker))
	;
	while (++i < table->params.nb_philos)
		pthread_detach(philos[i]->philo);
}

void	prepare_table(t_params args)
{
	t_philos_table	*table;

	if (init(&table, args))
		return ;
	*table->died = 0;
	philosophy_start(table);
}
