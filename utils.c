#include "philo.h"

void exit_error(char *str, t_data *data)
{
    printf("Error: %s\n", str);
    if(data && data->forks && data->philos)
        free_data(data);
    else if(data)
        free(data);
    exit(1);
}

long long get_time()
{
    struct timeval tv;
    int currnent_time;

    gettimeofday(&tv, NULL);
    currnent_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return currnent_time;
}

void print_status(t_philo *philo, t_data *data, char *msg)
{
    long long timestamp;

    pthread_mutex_lock(&data->print_lock);
    timestamp = get_time() - data->start_time;
    printf("%lld, %d, %s\n", timestamp, philo->id, msg);
    pthread_mutex_unlock(&data->print_lock);
}

void free_data(t_data *data)
{
    int i;
    
    i = 0;
    while(i < data->num_of_philo)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    free(data->forks);
    free(data->philos);
    pthread_mutex_destroy(&data->print_lock);
    pthread_mutex_destroy(&data->running_lock);
    free(data);
}
void check_running_lock(t_data *data)
{
    pthread_mutex_lock(&data->running_lock);
    if(!data->is_running)
    {
        pthread_mutex_unlock(&data->running_lock);
        return;
    }
    pthread_mutex_unlock(&data->running_lock);
}
// int	ft_usleep(useconds_t time)
// {
// 	u_int64_t	start;

// 	start = get_time();
// 	while ((get_time() - start) < time)
// 		usleep(time / 10);
// 	return (0);
// }


