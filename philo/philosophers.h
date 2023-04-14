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
	struct timeval	start_time;
	int			id;
	int			eat_counter;
	t_params 	params;
	pthread_t	philo;
	pthread_mutex_t	*left_fork;
	struct timeval last_meal;
	pthread_mutex_t	*right_fork;
}t_philo;
typedef struct s_philos_table
{
	t_params		params;
	t_philo			**philos;
	pthread_mutex_t **forks;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct timeval	start_time;
}t_philos_table;
int		init(t_philos_table **table, t_params arg);
long	ft_atoi(const char *nptr);
void	prepare_table(t_params args);
int		ft_isdigit(char c);
int		parsing(int ac, char **av, t_params *params);
void	ft_putstr_fd(char const *s, int fd);
void	show_error(char *s);
void print_philos_dot(t_philo **philos, int nb_philos);
void free_mutexes(pthread_mutex_t **ptr, int size);
long long get_time_in_ms(struct timeval time_par, int checker);
#endif
