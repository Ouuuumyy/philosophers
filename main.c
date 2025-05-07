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
    //free_data(data);
    return 0;
}