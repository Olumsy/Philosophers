
#include "philosophers.h"

static void	set_forks(pthread_mutex_t forks[], size_t id, t_philo_data *pdata)
{
	forks[0] = pdata->forks[id];
	if (id < (size_t)(pdata->philo_n - 1))
		forks[1] = pdata->forks[id + id];
	else
	{
		forks[1] = forks[0];
		forks[0] = pdata->forks[0];
	}
}

static void	eat(size_t id)
{
	printf("%ld is eating\n", id);
}

static void	sleep_mimimi(size_t id)
{
	printf("%ld is sleeping\n", id);
}

static void	think(size_t id)
{
	printf("%ld is thinking\n", id);
}

static int	get_id()
{
	static int i = 0;
	return (i++);
}

void	*philo_main(void *args)
{
	struct timeval		stime;
	ssize_t				count;
	pthread_mutex_t		forks[2];	
	const size_t		id = get_id();
	const t_philo_data	*pdata = (t_philo_data *) args;

	gettimeofday(&stime, NULL);
	count = 0;
	set_forks(forks, id, (t_philo_data *) pdata);
	while (count++ < pdata->stats.goal)
	{
		pthread_mutex_lock(&forks[0]);
		pthread_mutex_lock(&forks[1]);
		eat(id);
		pthread_mutex_unlock(&forks[0]);
		pthread_mutex_unlock(&forks[1]);
		sleep_mimimi(id);
		think(id);
	}
	return (0);
}
