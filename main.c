#include "philo.h"


void* routine(void *arg)
{
    printf("created philosopher\n");
}

void init_philo(t_philo *philo, char **av)
{
    philo->num_of_philo = atoi(av[1]);
    philo->time_to_die = atoi(av[2]);
    philo->time_to_eat = atoi(av[3]);
    philo->time_to_think = atoi(av[4]);
}

int main(int ac, char **av)
{
    int i = 0;
    t_philo *philo;
    if(ac < 5)
    {
        perror("invalid parametters\n");
        return 2;
    }
    philo = malloc(sizeof(t_philo));
    //parsing(ac, av);
    init_philo(philo, av);
    pthread_t ph[philo->num_of_philo];
    while(i < philo->num_of_philo)
    {
        if(pthread_create(ph + i, NULL, routine, NULL) != 0)
        {
            perror("cannot create thread\n");
            return 1;
        }
        i++;
    }
    i = 0;
    while(i < philo->num_of_philo)
    {
        if(pthread_join(ph[i], NULL) != 0)
        {
            perror("cannot end thread\n");
            return 1;
        }
        i++;
    }
}