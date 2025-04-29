#include <pthread.h>
#include <stdio.h>
#include<unistd.h>

int mails;
pthread_mutex_t mutex;

void *test()
{
    int i = 0;

    while(i < 1000000)
    {
        pthread_mutex_lock(&mutex);
        mails++;
        i++;
        pthread_mutex_unlock(&mutex);
    }

}

int main()
{
    pthread_t thr1, thr2;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&thr1, NULL, test, NULL);
    pthread_create(&thr2, NULL, test, NULL);
    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);
    pthread_mutex_destroy(&mutex);
    printf("%d\n", mails);
    return 0;
}