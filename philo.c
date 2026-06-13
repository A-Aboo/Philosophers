#include "header.h"





int main(int argc, char **argv){


t_data	data;

	if (argc != 5 && argc != 6)
		return (printf("Error: wrong number of arguments\n"), 1);

	if (init_data(&data, argc, argv) != 0)
		return (printf("Error: invalid arguments\n"), 1);

	if (init_mutexes(&data) != 0)
		return (printf("Error: mutex init failed\n"), 1);

	init_philos(&data);

	// later:
	// create_threads(&data);
	// monitor(&data);
	// join_threads(&data);
	// clean(&data);

	return (0);
   
}