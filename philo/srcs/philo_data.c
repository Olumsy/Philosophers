/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiteri <lspiteri@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:54:52 by lspiteri          #+#    #+#             */
/*   Updated: 2025/12/10 21:42:09 by lspiteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo_data	*init_philo_data(void)
{
	t_philo_data	*pdata;

	pdata = malloc(sizeof(t_philo_data) * 1);
	if (!pdata)
		return (NULL);
	pdata->forks = NULL;
	pdata->times_mutex = NULL;
	pdata->times = NULL;
	pdata->death_mutex = NULL;
	ft_memset(pdata->actions, 0, sizeof(pdata->actions));
	pdata->stats.philo_n = 0;
	pdata->stats.goal = -1;
	pdata->current_goal = 0;
	pdata->death_bool = 0;
	pdata->print = 0;
	pdata->start_time = 0;
	pdata->stats.time_die = 0;
	pdata->stats.time_eat = 0;
	pdata->stats.time_sleep = 0;
	return (pdata);
}

static int	mutex_farm(pthread_mutex_t **m, size_t n)
{
	int	i;

	if (!n)
		return (1);
	*m = malloc(sizeof(pthread_mutex_t) * n);
	if (*m == NULL)
		return (1);
	i = 0;
	while ((size_t) i < n)
		pthread_mutex_init(&((*m)[i++]), NULL);
	return (0);
}

int	pdata_filler(char **arg, t_philo_data *pdata)
{
	pdata->stats.philo_n = ft_atoi(arg[1]);
	pdata->start_time = get_time_us();
	pdata->stats.time_die = ft_atoi(arg[2]);
	pdata->stats.time_eat = ft_atoi(arg[3]);
	pdata->stats.time_sleep = ft_atoi(arg[4]);
	if (arg[5])
		pdata->stats.goal = ft_atoi(arg[5]);
	if (mutex_farm(&pdata->forks, pdata->stats.philo_n) || \
			mutex_farm(&pdata->times_mutex, pdata->stats.philo_n) || \
			mutex_farm(&pdata->death_mutex, 1) || \
			mutex_farm(&pdata->print, 1) || \
			mutex_farm(&pdata->start, 1))
		return (pdata_destructor(pdata), 1);
	pthread_mutex_lock(pdata->start);
	pdata->times = malloc(sizeof(long) * pdata->stats.philo_n);
	if (pdata->times == NULL)
		return (pdata_destructor(pdata), 1);
	ft_memset(pdata->times, 0, sizeof(long) * pdata->stats.philo_n);
	actions_arr(pdata->actions);
	return (0);
}

static void	mutex_destroy(pthread_mutex_t *m, int n)
{
	if (!m)
		return ;
	while (--n >= 0)
	{
		pthread_mutex_destroy(&(m[n]));
	}
	free(m);
	m = NULL;
}

void	pdata_destructor(t_philo_data *pdata)
{
	if (!pdata)
		return ;
	mutex_destroy(pdata->forks, pdata->stats.philo_n);
	mutex_destroy(pdata->times_mutex, pdata->stats.philo_n);
	mutex_destroy(pdata->death_mutex, 1);
	mutex_destroy(pdata->print, 1);
	mutex_destroy(pdata->start, 1);
	if (pdata->times)
	{
		free(pdata->times);
		pdata->times = NULL;
	}
	free(pdata);
}
