
#include "philosophers.h"

t_philo_data	*init_philo_data(void)
{
	t_philo_data	*pdata;

	pdata = malloc(sizeof(t_philo_data) * 1);
	if (!pdata)
		return (NULL);
	pdata->forks = NULL;
	pdata->philo_n = 0;
	pdata->stats.goal = -1;
	pdata->current_goal = 0;
	pdata->stop = 0;
	pdata->stats.time_die = 0;
	pdata->stats.time_eat = 0;
	pdata->stats.time_sleep = 0;
	return (pdata);
}

int	pdata_filler(char **arg, t_philo_data *pdata)
{
	pdata->philo_n = ft_atoi(arg[1]);
	pdata->forks = malloc(sizeof(pthread_mutex_t) * pdata->philo_n);
	if (pdata->forks == NULL)
		return (1);
	for (int i = 0; (size_t)i < pdata->philo_n; i++)
		pthread_mutex_init(&pdata->forks[i], NULL);
	pdata->stats.time_die = ft_atoi(arg[2]);
	pdata->stats.time_sleep = ft_atoi(arg[3]);
	if (arg[4])
		pdata->stats.goal = ft_atoi(arg[4]);
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
	free(pdata);
}
