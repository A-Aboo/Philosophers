#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				num_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_times_to_eat;
	int				dead_flag;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philos;
}	t_data;

int	init_data(t_data *data, int argc, char **argv);
int	init_mutexes(t_data *data);
void	init_philos(t_data *data);
long	ft_atol(char *str);
long	get_time_ms(void);
int		create_threads(t_data *data);
void	join_threads(t_data *data);
void	*routine(void *arg);
int		is_dead(t_data *data);
void	print_m(t_philo *philo, char *msg);
void	precise_sleep(long time_ms, t_data *data);
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);


#endif