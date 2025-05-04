# include "philo.h"

static char *lu_to_str(unsigned long n, char buffer[21])
{
	int		i = 20;

	buffer[i] = '\0';

	if (n == 0)
		buffer[--i] = '0';

	while (n > 0)
	{
		buffer[--i] = (n % 10) + '0';
		n /= 10;
	}
	return (&buffer[i]);
}

t_uint get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

void	print_action(t_action action, t_philo *philo)
{
	char	buffer1[21];
	char	buffer2[21];
	char	*str;
	char	*temp;
	char	*action_str;

	str = lu_to_str(get_time(), buffer1);
	str = ft_strjoin(str, " ");
	temp = str;
	str = ft_strjoin(temp, lu_to_str(philo->id, buffer2));
	free(temp);
	if (action == TAKEN_FORK)
		action_str = " has taken a fork\n";
	else if (action == EATING)
		action_str = " is eating\n";
	else if (action == SLEEPING)
		action_str = " is sleeping\n";
	else if (action == THINKING)
		action_str = " is thinking\n";
	else if (action == DIED)
		action_str = " died\n";
	temp = str;
	str = ft_strjoin(temp, action_str);
	free(temp);
	write(1, str, ft_strlen(str));
	free(str);
}


//int main()
//{
//	print_action(TAKEN_FORK, NULL);
//}


	//write(1, buffer, ft_strlen(buffer));

	//	//ft_putul(get_time());
	//	printf("%u", get_time());
	//	write(1, " ", 1);
	//	printf("%u", philo->id);
	//	//ft_putul(philo->id);
	//if (action == TAKEN_FORK)
	//	write(1, " has taken a fork\n", 18);
	//else if (action == EATING)
	//	write(1, " is eating\n", 11);
	//else if (action == SLEEPING)
	//	write(1, " is sleeping\n", 13);
	//else if (action == THINKING)
	//	write(1, " is thinking\n", 14);
	//else if (action == DIED)
	//	write(1, " died\n", 6);