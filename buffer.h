#ifndef BUFFER_H  
#define BUFFER_H

#include <arpa/inet.h>

typedef struct __attribute__((packed)) Rocket
{
    uint32_t timestamp; // (uint32_t)time(NULL);
    float altitude;
    float speed;
} Rocket;

typedef struct RingBuffer
{
    Rocket rocket_arr[5];
    int head;
    int tail;
} RingBuffer;

typedef struct {
    Rocket *roket_ptr;  
    RingBuffer *ring_ptr;   
} Threads;

extern pthread_mutex_t mutex;

void read_value(RingBuffer *rb);
void add_val(Rocket *rocket, RingBuffer *rb);
void *add_wrapper(void *arg);
void *read_wrapper(void *arg);

#endif