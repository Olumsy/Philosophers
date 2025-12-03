
#include "philosophers.h"

t_philo_data	*init_philo_data(void)
{
	t_philo_data	*pdata;

	pdata = malloc(sizeof(t_philo_data) * 1);
	if (!pdata)
		return (NULL);
	pdata->forks = NULL;
	pdata->times = NULL;
	pdata->death_mutex = NULL;
	ft_memset(pdata->actions, 0, sizeof(pdata->actions));
	pdata->stats.philo_n = 0;
	pdata->stats.goal = -1;
	pdata->current_goal = 0;
	pdata->death_bool = 0;
	pdata->start_time = 0;
	pdata->stats.time_die = 0;
	pdata->stats.time_eat = 0;
	pdata->stats.time_sleep = 0;
	return (pdata);
}

int	pdata_filler(char **arg, t_philo_data *pdata)
{
	int	i;

	pdata->stats.philo_n = ft_atoi(arg[1]);
	pdata->start_time = get_time_ms();
	pdata->stats.time_die = ft_atoi(arg[2]);
	pdata->stats.time_eat = ft_atoi(arg[3]);
	pdata->stats.time_sleep = ft_atoi(arg[4]);
	if (arg[5])
		pdata->stats.goal = ft_atoi(arg[5]);
	pdata->forks = malloc(sizeof(pthread_mutex_t) * pdata->stats.philo_n);
	if (pdata->forks == NULL)
		return (pdata_destructor(pdata), 1);
	i = 0;
	while ((size_t) i < pdata->stats.philo_n)
		pthread_mutex_init(&pdata->forks[i++], NULL);
	pdata->death_mutex = malloc(sizeof(pthread_mutex_t) * 1);
	if (!pdata->death_mutex)
		return (pdata_destructor(pdata), 1);
	pdata->times = malloc(sizeof(long) * pdata->stats.philo_n);
	if (pdata->times == NULL)
		return (pdata_destructor(pdata), 1);
	ft_memset(pdata->times, 0, sizeof(pdata->times) * pdata->stats.philo_n);
	pthread_mutex_init(pdata->death_mutex, NULL);
	actions_arr(pdata->actions);
	return (0);
}

void	pdata_destructor(t_philo_data *pdata)
{
	if (!pdata)
		return ;
	if (pdata->forks)
	{
		free(pdata->forks);
		pdata->forks = NULL;
	}
	if (pdata->death_mutex)
	{
		free(pdata->death_mutex);
		pdata->death_mutex = NULL;
	}
	if (pdata->times)
	{
		free(pdata->times);
		pdata->times = NULL;
	}
	free(pdata);
}
