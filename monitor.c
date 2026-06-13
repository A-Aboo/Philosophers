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