#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <time.h>
#include "buffer.h"

#define PORT 8080
#define BUFFER_SIZE 1024

int sockfd;
struct sockaddr_in server_addr, client_addr;
int n;
socklen_t len = sizeof(client_addr);

void server()
{
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket ERROR");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind ERROR");
        exit(EXIT_FAILURE);
    }
    printf("UDP %d listen...\n", PORT);
}

int main()
{
    server();

    pthread_mutex_init(&mutex, NULL);

    RingBuffer rb;
    pthread_t thread2;

    while (1)
    {
        n = recvfrom(sockfd, &rb, sizeof(rb), 0,
                     (struct sockaddr *)&client_addr, &len);

        pthread_create(&thread2, NULL, read_wrapper, &rb);
        pthread_join(thread2, NULL);

        int last_read_index = (rb.tail - 1 + 5) % 5;

        if (rb.rocket_arr[last_read_index].altitude <= 0 && rb.rocket_arr[last_read_index].speed > 0)
        {
            printf("Rocket impact detected!\n");
            break;
        }
    }

    close(sockfd);
    pthread_mutex_destroy(&mutex);
    return 0;
}