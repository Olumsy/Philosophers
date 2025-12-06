/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspiteri <lspiteri@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:28:25 by lspiteri          #+#    #+#             */
/*   Updated: 2025/12/06 17:40:49 by lspiteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parsing(t_philo_data *pdata)
{
	if (pdata->stats.philo_n <= 0 || \
		pdata->stats.time_die <= 0 || pdata->stats.time_die >= || \
		pdata->stats.time_eat <= 0 || \
		pdata->stats.time_sleep <= 0 || \
