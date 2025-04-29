#include "philo.h"

int is_digit(char *str)
{
    int i;

    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] < '0' || str[i] > '9')
            return (1);
        i++;
    }
    return (0);
}

int	ft_atoi(const char *str)
{
	int	n;
	int	i;
	int	min;

	n = 0;
	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		n = n * 10 + str[i++] - 48;
	return (n);
}

void parsing(int ac, char **av)
{
    int i;
    int num;

    i = 1;
    while(i <= ac)
    {
        if(is_digit(av[i]) != 0)
        {
            perror("not an int\n");
            exit(1);
        }
        num = ft_atoi(av[i]);
    }
}