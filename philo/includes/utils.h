
#ifndef UTILS_H
# define UTILS_H

int		ft_atoi(const char *str);
long	get_time_us(void);
long	get_time_ms(void);
void	*ft_memset(void *b0, int c, size_t len);

void	psleep(long t_start, long t, long p);
# ifndef P
#  define P 125
# endif

#endif
