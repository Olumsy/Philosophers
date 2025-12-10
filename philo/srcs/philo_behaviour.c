/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behaviour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiteri <lspiteri@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:55:28 by lspiteri          #+#    #+#             */
/*   Updated: 2025/12/08 16:17:23 by lspiteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	static int				id = -1;
	id++;
	return (id);
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
	usleep(1000 * (id % 2));
}

void	*philo_main(void *args)
{
	ssize_t					count;
	pthread_mutex_t			*forks[2];	
	static pthread_mutex_t	id_mutex = PTHREAD_MUTEX_INITIALIZER;
	size_t					id;
	const t_philo_data		*pdata = (t_philo_data *) args;

	pthread_mutex_lock(&id_mutex);
	id = get_id();
	pthread_mutex_unlock(&id_mutex);
	wait_start(id, (t_philo_data *) pdata);
	count = 0;
	if (set_forks(forks, id, (t_philo_data *) pdata))
		return (0);
	while (count < pdata->stats.goal * 2-  1 || pdata->stats.goal == -1)
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
