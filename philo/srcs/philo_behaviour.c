
#include "philosophers.h"

static void	set_forks(pthread_mutex_t *forks[], size_t id, t_philo_data *pdata)
{
	forks[0] = &pdata->forks[id];
	if (id < (size_t)(pdata->stats.philo_n - 1))
		forks[1] = &pdata->forks[id + 1];
	else
	{
		forks[1] = forks[0];
		forks[0] = &pdata->forks[0];
	}
//	printf("> %ld, forks{%p, %p}\n", id, forks[0], forks[1]);
}

static int	get_id()
{
	static int i = 0;
	return (i++);
}

void	monitor(t_philo_data *pdata)
{
	size_t	i;

	i = 0;
	printf("yo\n");
	while (1)
	{
		//printf("> %ld, %ld ate at %ld\n", get_time_ms(), i, pdata->times[i]);
		if (pdata->times[i] && pdata->times[i] < (long)(get_time_us() - (pdata->stats.time_die * 1000)))
			printf("y a un mort la %ld\n", get_time_ms() - pdata->times[i]);
		if (i++ == pdata->stats.philo_n)
			i = 0;
	}
}

void	*philo_main(void *args)
{
	long				stime;
	ssize_t				count;
	pthread_mutex_t		*forks[2];	
	const size_t		id = get_id();
	const t_philo_data	*pdata = (t_philo_data *) args;

	stime = get_time_ms();
	(void)stime;
	count = 0;
	set_forks(forks, id, (t_philo_data *) pdata);
	while (count < pdata->stats.goal * 2 - 1 || pdata->stats.goal == -1)
	{
		if (pdata->actions[count % 2](id, forks, (t_philo_data *)pdata))
			printf("dead\n");
		stime = get_time_ms();
		count++;
	}
	return (0);
}
