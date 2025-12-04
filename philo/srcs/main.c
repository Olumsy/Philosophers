
#include "philosophers.h"

static int	start_philo(t_philo_data *pdata)
{
	int	i;
	int	n;

	n = pdata->stats.philo_n;
	pthread_t *threads = malloc(sizeof(pthread_t) * n);
	if (!threads)
		return (1);
	i = 0;
	while (i < n)
		pthread_create(&threads[i++], NULL, philo_main, (void *)pdata);
	monitor(pdata);
	i = 0;
	while (i < n)
		pthread_join(threads[i++], NULL);
	free(threads);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_data	*pdata;

	if (argc < 4)
		return (printf(" Usage: ./philo number_of_philosophers \
		time_to_die \
		time_to_eat time_to_sleep \
		[number_of_times_each_philosopher_must_eat]"), 1);
	pdata = init_philo_data();
	if (pdata_filler(argv, pdata))
		return (pdata_destructor(pdata), 1);
//	for (int i = 0; (size_t)i < pdata->stats.philo_n; i++)
//		printf("> &pdata->forks[%d], %p\n", i, &pdata->forks[i]);
	start_philo(pdata);
	return (pdata_destructor(pdata), 0);
}
