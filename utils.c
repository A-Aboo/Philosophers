#include "header.h"


long	ft_atol(char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

long	get_time_ms(void) // sends tims in milliseconds 
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	create_threads(t_data *data)
{
	int	i;

	data->start_time = get_time_ms(); // assigns the start time for each philo calles the other function 
	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].last_meal = data->start_time; // each philo is considered fed cause the last meal time is = creation time 
		if (pthread_create(&data->philos[i].thread, NULL, // creates a thread for each philo 
				philosopher, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("Philo %d started\n", philo->id);
	return (NULL);
}

void	join_threads(t_data *data) // the pthread_join is used for each philosophers to make the main wait till the thread end its task 
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)// for each philosophers the main should wait and not end 
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}