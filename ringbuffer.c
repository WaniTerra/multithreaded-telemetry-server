

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "buffer.h"

pthread_mutex_t mutex;

void add_val(Rocket *rocket, RingBuffer *rb)
{
    pthread_mutex_lock(&mutex);

    int next_head = (rb->head + 1) % 5;

    if (next_head == rb->tail)
    {
        printf("Buffer Full! Cannot add\n");
        pthread_mutex_unlock(&mutex);
        return;
    }
    printf("Added\n");
    rb->rocket_arr[rb->head] = *rocket;

    rb->head = next_head;

    pthread_mutex_unlock(&mutex);
}

void read_value(RingBuffer *rb)
{

    pthread_mutex_lock(&mutex);

    if (rb->head == rb->tail)
    {
        printf("\nBuffer Empty! Nothing to read.\n");
        pthread_mutex_unlock(&mutex);
        return;
    }

    time_t raw_time = (time_t)rb->rocket_arr[rb->tail].timestamp;

    printf("--------------------------------\n");
    printf("Time          : %s\n", ctime(&raw_time));
    printf("Altitude      : %f\n", rb->rocket_arr[rb->tail].altitude);
    printf("Speed         : %f", rb->rocket_arr[rb->tail].speed);

    rb->tail = (rb->tail + 1) % 5;

    pthread_mutex_unlock(&mutex);
}

void *add_wrapper(void *arg)
{

    Threads *data = (Threads *)arg;

    add_val(data->roket_ptr, data->ring_ptr);

    return NULL;
}

void *read_wrapper(void *arg) {
    RingBuffer *rb = (RingBuffer *)arg;
    read_value(rb);
    return NULL;
}