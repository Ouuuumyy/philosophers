#include "philo.h"

int is_digit(char *str)
{
    int i;

    i = 0;

    while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
    if(str[i] == '\0')
        return(1);
    while(str[i] != '\0')
    {
        if(str[i] < '0' || str[i] > '9')
            return (1);
        i++;
    }
    return (0);
}
void exit_error(char *str, t_data *data)
{
    printf("Error: %s", str);
    free(data);
    exit(1);
}

int	ft_atoi(const char *str, t_data *data)
{
	long	n;
	int	i;
	int	min;

	n = 0;
	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
    {
		n = n * 10 + str[i++] - 48;
        if(n > INT_MAX)
            exit_error("argument exceeds max int\n", data);
    }
	return ((int)n);
}

void parsing(int ac, char **av, t_data *data)
{
    int i;
    int num;

    i = 1;
    if(ac < 5 || ac > 6)
        exit_error("uncorrect number of arguments\n", data);
    while(i < ac)
    {
        if(is_digit(av[i]) != 0)
            exit_error("you must enter a positive number\n", data);
        num = ft_atoi(av[i], data);
        if(num == 0)
            exit_error("arguments must be > 0\n", data);
        // else if(i == 1 && num == 1)
        //     exit_error("only one philosopher, philosopher will always die\n", data);
        i++;
    }
}

