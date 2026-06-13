#include "header.h"

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_dead(philo->data))
	{
		take_forks(philo);
		eat(philo);
		print_m(philo, "is sleeping");
		precise_sleep(philo->data->time_to_sleep, philo->data);
		print_m(philo, "is thinking");
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

void	monitor(t_data *data) // checks that no one is dead 
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
		usleep(500);
	}
}