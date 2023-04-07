#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

typedef struct s_params
{
	long nb_philos;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	long eat_count;
}t_params;
typedef struct s_philo
{
	pthread_t	*philo;
	int			id;
}t_philo;
typedef struct s_philos_table
{
	int id;
	t_params		params;
	t_philo			*philos;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}t_philos_table;
long	ft_atoi(const char *nptr);
void	prepare_table(t_params args);
int		ft_isdigit(char c);
int		parsing(int ac, char **av, t_params *params);
void	ft_putstr_fd(char const *s, int fd);
void	show_error(char *s);
#endif
