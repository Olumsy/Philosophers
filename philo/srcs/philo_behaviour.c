
#include "philosophers.h"

static int	set_forks(pthread_mutex_t *forks[], size_t id, t_philo_data *pdata)
{
	forks[0] = &pdata->forks[id];
	if (id < (size_t)(pdata->stats.philo_n - 1))
		forks[1] = &pdata->forks[id + 1];
	else
	{
		forks[1] = forks[0];
		forks[0] = &pdata->forks[0];
	}
	return ((forks[0] == forks[1]));
}

static int	get_id()
{
	static int i = 0;
	return (i++);
}

static void	wait_start(size_t id, t_philo_data *pdata)
{
	pthread_mutex_lock(&pdata->times_mutex[id]);
	pdata->times[id] = get_time_us();
	pthread_mutex_unlock(&pdata->times_mutex[id]);
	pthread_mutex_lock(pdata->start);
	pthread_mutex_unlock(pdata->start);
	pthread_mutex_lock(&pdata->times_mutex[id]);
	pdata->times[id] = get_time_us();
	pthread_mutex_unlock(&pdata->times_mutex[id]);
}

void	*philo_main(void *args)
{
	ssize_t				count;
	pthread_mutex_t		*forks[2];	
	const size_t		id = get_id();
	const t_philo_data	*pdata = (t_philo_data *) args;

	wait_start(id, (t_philo_data *) pdata);
	count = 0;
	if (set_forks(forks, id, (t_philo_data *) pdata))
		return (0);
	while (count < pdata->stats.goal * 2 - 1 || pdata->stats.goal == -1)
	{
		if (pdata->actions[count % 2](id, forks, (t_philo_data *)pdata))
			break ;
		count++;
	}
	pthread_mutex_lock(&pdata->times_mutex[id]);
	pdata->times[id] = 0;
	pthread_mutex_unlock(&pdata->times_mutex[id]);
	return (0);
}
