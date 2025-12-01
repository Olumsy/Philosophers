
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
