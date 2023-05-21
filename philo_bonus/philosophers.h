#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <fcntl.h>
#include <semaphore.h>
typedef struct s_philo_checker t_philo_checker;
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
	t_params	params;
	pid_t	pid;
	sem_t *rfork;
	sem_t *lfork;
	sem_t *print;
	pthread_t thread;
	struct timeval	last_meal;
}t_philo;

typedef struct s_philos_table
{
	int				start;
	t_params		params;
	t_philo			**philos;
	int				*philos_stat;
	sem_t	*lfork;
	sem_t	*print;
	sem_t	*rfork;
	t_philo_checker	*checker_ptr;
	struct timeval	start_time;
}t_philos_table;
typedef struct s_philo_checker
{
	long long	current_time;
	pthread_t	death_checker;
	t_philos_table	*table;
}t_philo_checker;
int		ft_strcmp(char *s1, char *s2);
int		init(t_philos_table **table, t_params arg);
long	ft_atoi(const char *nptr);
void	prepare_table(t_params args);
int		ft_isdigit(char c);
int		parsing(int ac, char **av, t_params *params);
void	free_ptrs(void **ptr, int size);
void	ft_putstr_fd(char const *s, int fd);
void	__lock_print(char *str, int id,t_philo *philo);
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	*ft_malloc(size_t size);
void	philo_eat(t_philo *philo);
void	philo_take_fork(t_philo	*philo);
long long get_curr_time(t_philos_table *table, struct timeval time);
struct timeval get_timeval();
void cleanup_processes();
void	ft_usleep(long long time);
pid_t		ft_fork();
void *philosopher_routine(void *ptr);
void		show_error(char *s);
void		free_mutexes(t_philos_table *table);
long long	get_time_in_ms(struct timeval time_par, int checker);
#endif
