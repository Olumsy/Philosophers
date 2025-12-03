
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

typedef struct	s_philo_data t_philo_data;

typedef int (*t_action)(size_t id, pthread_mutex_t *forks[], t_philo_data *pdata);

typedef struct s_philo_data
{
	pthread_mutex_t	*forks;
	long			*times;
	t_action		actions[4];
	size_t			current_goal;
	pthread_mutex_t	*death_mutex;
	bool			death_bool;
	long			start_time;
	struct	s_stats
	{
		size_t	philo_n;
		size_t	time_die;
		size_t	time_eat;
		size_t	time_sleep;
		ssize_t	goal;
	}	stats;
}	t_philo_data;

t_philo_data	*init_philo_data(void);
int				pdata_filler(char **arg, t_philo_data *pdata);
void			pdata_destructor(t_philo_data *pdata);
void			*philo_main(void *args);
void			monitor(t_philo_data *pdata);
void			actions_arr(t_action actions[]);
int 			is_dead(t_philo_data *pdata);

#endif
