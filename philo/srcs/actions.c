
#include "philosophers.h"

static int	act_eat(size_t id, pthread_mutex_t *forks[], t_philo_data *pdata)
{
	long	t_start;

	pthread_mutex_lock(forks[0]);
	pthread_mutex_lock(forks[1]);
	t_start = get_time_us();
	if (is_dead(pdata))
		return (pthread_mutex_unlock(forks[0]), \
		pthread_mutex_unlock(forks[1]), 1);
	pdata->times[id] = t_start;
	printf("%ld %ld is eating\n", (get_time_ms() - pdata->start_time), id);
	psleep(t_start, pdata->stats.time_eat * 1000, \
	(pdata->stats.time_eat / 100) * P);
	pthread_mutex_unlock(forks[0]);
	pthread_mutex_unlock(forks[1]);
	return (0);
}

static int	act_sleep(size_t id, pthread_mutex_t *forks[], t_philo_data *pdata)
{
	long	t_start;

	(void) forks;
	if (is_dead(pdata))
		return (1);
	t_start = get_time_us();
	printf("%ld %ld is sleeping\n", get_time_ms() - pdata->start_time, id);
	psleep(t_start, pdata->stats.time_sleep * 1000, \
	(pdata->stats.time_sleep /100) * P);
	if (is_dead(pdata))
		return (1);
	printf("%ld %ld is thinking\n", get_time_ms() - pdata->start_time, id);
	return (0);
}

static int	act_think(size_t id, pthread_mutex_t *forks[], t_philo_data *pdata)
{
	(void) forks;
	if (is_dead(pdata))
		return (1);
	printf("%ld %ld is thinking\n", get_time_ms() - pdata->start_time, id);
	return (0);
}

void	actions_arr(t_action actions[])
{
	actions[0] = act_eat;
	actions[1] = act_sleep;
	actions[2] = act_think;
}

int is_dead(t_philo_data *pdata)
{
	int	ret;

	pthread_mutex_lock(pdata->death_mutex);
		ret = pdata->death_bool;
	pthread_mutex_unlock(pdata->death_mutex);
	return (ret);
}
