#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int x = 2;

void *routin()
{
    // printf("Processes id %d\n", getpid());
    x++;
    sleep(2);
    printf("Value of x: %d\n", x);
}

void *routin2()
{
    sleep(2);
    printf("Value of x: %d\n", x);
}

int main(int argc, char **argv)
{
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &routin, NULL))
    {
        return (1);
    }
    if (pthread_create(&t2, NULL, &routin, NULL))
    {
        return (2);
    }
    if (pthread_join(t1, NULL))
    {
        return (3);
    }
    if (pthread_join(t2, NULL))
    {
        return (3);
    }
    return (0);
}