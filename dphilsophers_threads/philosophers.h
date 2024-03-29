/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghouzra <rghouzra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:35:58 by rghouzra          #+#    #+#             */
/*   Updated: 2023/06/07 09:11:45 by rghouzra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo_checker	t_philo_checker;
typedef struct s_params
{
	long						nb_philos;
	long						ttd;
	long						tte;
	long						tts;
	long						eat_count;
}								t_params;
typedef struct s_philo
{
	struct timeval				start_time;
	int							id;
	int							eat_counter;
	t_params					params;
	pthread_t					philo;
	pthread_mutex_t				*meal;
	pthread_mutex_t				*stat;
	pthread_mutex_t				*eat_count;
	pthread_mutex_t				*left_fork;
	struct timeval				last_meal;
	int							*died_ptr;
	pthread_mutex_t				*right_fork;
	pthread_mutex_t				*print;
}								t_philo;

typedef struct s_philos_table
{
	int							start;
	t_params					params;
	t_philo						**philos;
	int							*philos_stat;
	int							*died;
	t_philo_checker				*checker_ptr;
	pthread_mutex_t				*stats;
	pthread_mutex_t				**meals;
	pthread_mutex_t				**forks;
	pthread_mutex_t				*print;
	pthread_mutex_t				**eat_counts;
	struct timeval				start_time;
}								t_philos_table;
typedef struct s_philo_checker
{
	long long					current_time;
	pthread_t					death_checker;
	pthread_mutex_t				*death;
	t_philos_table				*table;
}								t_philo_checker;
int								ft_strcmp(char *s1, char *s2);
int								init(t_philos_table **table, t_params arg);
long							ft_atoi(const char *nptr);
t_philos_table					*prepare_table(t_params args);
int								ft_isdigit(char c);
int								check_death(t_philos_table *table, int index);
int								parsing(int ac, char **av, t_params *params);
void							ft_putstr_fd(char const *s, int fd);
void							__lock_print(char *str, int id, t_philo *philo);
void							philo_think(t_philo *philo);
void							philo_sleep(t_philo *philo);
void							philo_eat(t_philo *philo);
void							philo_take_fork(t_philo *philo);
void							delete_garbage(t_philos_table **table);
void							ft_usleep(long long time);
void							show_error(char *s);
void							free_mutexes(pthread_mutex_t **ptr, int size);
long long						get_time_in_ms(struct timeval time_par,
									int checker);
void							free_ptrs(void **ptr, int size);
#endif
