
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/time.h>
# include "utils.h"

typedef struct s_philo_data
{
	pthread_mutex_t	*forks;
	size_t			philo_n;
	size_t			current_goal;
	bool			stop;
	struct	s_stats
	{
		size_t	time_die;
		size_t	time_eat;
		size_t	time_sleep;
		ssize_t	goal;
	}	stats;
}	t_philo_data;

typedef struct	s_philo_args
{
    size_t			id;
    t_philo_data	*pdata;
}	t_philo_args;

t_philo_data	*init_philo_data(void);
int				pdata_filler(char **arg, t_philo_data *pdata);
void			pdata_destructor(t_philo_data *pdata);
void			*philo_main(void *args);

#endif
