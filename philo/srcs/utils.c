
#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	sign;

	i = 0;
	num = 0;
	sign = 1;
	while (str && ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' '))
	{
		i++;
	}
	if (str && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str && (str[i] >= '0' && str[i] <= '9'))
		num = num * 10 + (str[i++] - '0');
	return (num * sign);
}

long	get_time_us(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000000L + t.tv_usec);
}

long	get_time_ms(void)
{
    return (get_time_us() / 1000);
}

void	*ft_memset(void *b0, int c, size_t len)
{
	size_t			i;
	unsigned char	*b;

	b = b0;
	i = 0;
	while (i < len)
	{
		b[i++] = c;
	}
	return (b);
}

void	psleep(long t_start, long t, long p)
{
	long	now;
	long	end;
	long	remain;

	now = get_time_us();
	end = t_start + t;
	p = p || 100;
	while (now < end - (p - 10))
	{
		remain = end - now;
		if (remain > p)
			usleep(remain * 0.9);
		else
			usleep((p));
		now = get_time_us();
	}
}
