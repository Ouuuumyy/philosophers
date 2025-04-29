#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int primes[10] = {1, 21, 3, 6, 9, 12, 0, 89, 10, 4};

void *test(void *arg)
{
    printf("%d ", primes[*(int *)arg]);
    free(arg);
}

int main()
{
    pthread_t th[10];
    int i = 0;

    while(i < 10)
    {
        int *index = malloc(sizeof(int));
        *index = i;
        if(pthread_create(&th[i], NULL, test, index) != 0)
        {
            perror("can not create thread\n");
            return 1;
        }
        i++;
    }
    i = 0;
    while(i < 10)
    {
        if(pthread_join(th[i], NULL) != 0)
        {
            perror("can not end thread\n");
            return 2;
        }
        i++;
    }
}