#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#define BIG 1000000


struct s_data
{
    uint32_t *a;
    pthread_mutex_t *mutex;
};

void *change_a(void *arg)
{   
    struct s_data *data = (struct s_data *)arg;
    pthread_mutex_lock(data->mutex);
    uint32_t *a = (uint32_t *)data->a;
    for(uint32_t i = 0; i < BIG; i++)
        ((*data->a))++; 
    pthread_mutex_unlock(data->mutex);
    return (NULL);
}

int main()
{
    pthread_t thread_1;
    pthread_t thread_2;
    uint32_t a;
    pthread_mutex_t mutex;
    struct s_data data;

    pthread_mutex_init(&mutex, NULL);
    a = 0;
    data.a = &a;
    data.mutex = &mutex;

    pthread_create(&thread_1, NULL, change_a, &data); // Pass the address of 'data' instead of 'a'
    pthread_create(&thread_2, NULL, change_a, &data); // Pass the address of 'data' instead of 'a'
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    printf("a is: %d\n", a);
}