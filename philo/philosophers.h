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
	pthread_t *philos;

}t_philo;
long	ft_atoi(const char *nptr);
void    *ft_calloc(size_t nelem, size_t elsize);
void	philosophy_start(t_params args);
int		ft_isdigit(char c);
int		parsing(int ac, char **av, t_params *params);
void	ft_putstr_fd(char const *s, int fd);
void	show_error(char *s);
#endif
