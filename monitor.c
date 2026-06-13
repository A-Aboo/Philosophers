#include "header.h"

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, "has taken a fork");
		precise_sleep(philo->data->time_to_die, philo->data);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_dead(philo->data))
	{
		take_forks(philo);
		eat(philo);
		safe_print(philo, "is sleeping");
		precise_sleep(philo->data->time_to_sleep, philo->data);
		safe_print(philo, "is thinking");
	}
	return (NULL);
}

void	set_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	data->dead_flag = 1;
	pthread_mutex_unlock(&data->dead_lock);
}

int	check_philo_dead(t_philo *philo)
{
	long	now;
	long	last_meal;

	pthread_mutex_lock(&philo->data->meal_lock);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->data->meal_lock);

	now = get_time_ms();
	if (now - last_meal > philo->data->time_to_die) // if dead the set to dead print the time after simulation that he is dead and then exit 
	{
		set_dead(philo->data);
		pthread_mutex_lock(&philo->data->write_lock);
		printf("%ld %d died\n",
			get_time_ms() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->write_lock);
		return (1);
	}
	return (0);
}

void	monitor(t_data *data)
{
	int	i;

	while (!is_dead(data))
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			if (check_philo_dead(&data->philos[i]))
				return ;
			i++;
		}
		if (all_ate_enough(data))
		{
			set_dead(data);
			return ;
		}
		usleep(500);
	}
}

int	all_ate_enough(t_data *data)
{
	int	i;
	int	done;

	if (data->num_times_to_eat == -1)
		return (0);
	i = 0;
	done = 0;
	pthread_mutex_lock(&data->meal_lock);
	while (i < data->num_of_philos)
	{
		if (data->philos[i].meals_eaten >= data->num_times_to_eat)
			done++;
		i++;
	}
	pthread_mutex_unlock(&data->meal_lock);
	return (done == data->num_of_philos);
}