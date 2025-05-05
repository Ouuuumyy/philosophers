#include "philo.h"

int main(int ac, char **av)
{
    int i = 0;
    t_data *data;
    data = malloc(sizeof(t_data));
    parsing(ac, av, data);
    init_data(data, av);
    init_philosophers(data);
    create_threads(data);
    free(data->philos);
    while(i < data->num_of_philo)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    free(data->forks);
    pthread_mutex_destroy(&data->print_lock);
    free(data);
    return 0;
}