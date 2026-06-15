#include "header.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->num_of_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->num_times_to_eat = -1;
	if (argc == 6)
		data->num_times_to_eat = ft_atol(argv[5]);
	data->dead_flag = 0; // no philo is dead 
	data->start_time = 0; //
	if (data->num_of_philos <= 0 || data->time_to_die <= 0 // checking for invalid values 
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (1);
	if (argc == 6 && data->num_times_to_eat <= 0) // If the optional eating limit exists, it must be positive.
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->num_of_philos); // Allocates memory for all philosophers.
    if (!data->philos) 
        return (1);

    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
    if (!data->forks)
    {
        free(data->philos);
        return (1);
    }
	return (0);
}




int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		return (1);
	return (0);
}


void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;

		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1)
			% data->num_of_philos];

		i++;
	}
}   

