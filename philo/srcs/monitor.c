/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiteri <lspiteri@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:55:16 by lspiteri          #+#    #+#             */
/*   Updated: 2025/12/06 18:41:53 by lspiteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void set_death(t_philo_data *pdata)
{
	pthread_mutex_lock(pdata->death_mutex);
		pdata->death_bool = 1;
	pthread_mutex_unlock(pdata->death_mutex);
}

static long	get_last_time(size_t id, t_philo_data *pdata)
{
	long	ret;

	pthread_mutex_lock(&pdata->times_mutex[id]);
	ret = pdata->times[id];
	pthread_mutex_unlock(&pdata->times_mutex[id]);
	return (ret);
}

void	monitor(t_philo_data *pdata)
{
	size_t	i;
	long	t;
	bool	finished;

	i = 0;
	while (get_last_time(pdata->stats.philo_n - 1, pdata) == 0)
		;
	pdata->start_time = get_time_us();
	pthread_mutex_unlock(pdata->start);
	while (1)
	{
		t = get_last_time(i, pdata);
		if (t && t < (long)(get_time_us() - \
			(pdata->stats.time_die * 1000)))
		{
			set_death(pdata);
			break ;
		}
		finished = t == 0;
		if (++i == pdata->stats.philo_n)
		{
			if (finished == 1)
				return ;
			finished = 1;
			i = 0;
			usleep(500);
		}
	}
	pthread_mutex_lock(pdata->print);
	printf("%ld %ld died\n", (get_time_us() - pdata->start_time) / 1000, i + 1);
	pthread_mutex_unlock(pdata->print);
}
