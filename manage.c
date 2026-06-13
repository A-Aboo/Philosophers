#include "header.h"


int	is_dead(t_data *data)// checks if the simlation have ended 
{
	int	value;

	pthread_mutex_lock(&data->dead_lock); // lock it because the dead flag is shared between threads 
	value = data->dead_flag;
	pthread_mutex_unlock(&data->dead_lock); // unlocks back so another thread can now use it 
	return (value);
}

void	print_m(t_philo *philo, char *msg)
{
	long	time; // long for time 

	pthread_mutex_lock(&philo->data->write_lock); // locks the printing so two philosophers do not print at the same time 
	if (!is_dead(philo->data)) // prints only if the simulation is not ended
	{
		time = get_time_ms() - philo->data->start_time;
		printf("%ld %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	precise_sleep(long time_ms, t_data *data) // sleep of the philo 
{
	long	start;

	start = get_time_ms(); // take the start time of the sleep 
	while (!is_dead(data)) // checks if a phino is not dead 
	{
		if (get_time_ms() - start >= time_ms) // if enough time have passed for sleep then stop sleep 
			break ;
		usleep(500);
	}
}

void	take_forks(t_philo *philo) // takes the two fork if another philo has it waits 
{
	pthread_mutex_lock(philo->left_fork);
	print_m(philo, "has taken a fork");

	pthread_mutex_lock(philo->right_fork);
	print_m(philo, "has taken a fork");
}

void	eat(t_philo *philo)// update meal info eat and release the forks for the other phios 
{
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);

	print_m(philo, "is eating");
	precise_sleep(philo->data->time_to_eat, philo->data);

	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}