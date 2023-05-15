#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/syscall.h>

#define THREAD_MUN 2

void *routine(void *args)
{
    sleep(1);
    printf("Finished execution\n");
}

int main(int argc, char **argv)
{
    pthread_t th[THREAD_MUN];
    pthread_attr_t detachedThread;
    pthread_attr_init(&detachedThread);
    pthread_attr_setdetachstate(&detachedThread,PTHREAD_CREATE_DETACHED);
    int i;
    for (i = 0; i < THREAD_MUN; i++)
    {
        if (pthread_create(&th[i], &detachedThread, &routine, NULL) != 0)
        {
            perror("Failed to create thread");
        }
        pthread_detach(th[i]);
    }
    // for (i = 0; i < THREAD_MUN; i++)
    // {
    //     if (pthread_join(th[i], NULL) != 0)
    //     {
    //         perror("Failed to join thread");
    //     }
    // }
    pthread_attr_destroy(&detachedThread);
    pthread_exit(0);
    return (0);
}