/*
 * Created by Arkady Sahakyan.
 */

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "queue.h"

pthread_mutex_t mutex;
pthread_cond_t pcond;
pthread_cond_t ccond;

static const unsigned int X = 32768;
unsigned int iteration_counter = 0;

void* producer(void* args)
{
	for (int i = 0; i < X; i++)
	{
		pthread_mutex_lock(&mutex);
		while (queue_is_full())
			pthread_cond_wait(&pcond, &mutex);
		if (queue_is_empty())
			pthread_cond_signal(&ccond);
		queue_enqueue(rand() % (9999 + 1 - 0) + 0);
		iteration_counter++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void* consumer(void* args)
{
	for (int i = 0; i < X; i++)
	{
		pthread_mutex_lock(&mutex);
		while (queue_is_empty())
			pthread_cond_wait(&ccond, &mutex);
		if (queue_is_full())
			pthread_cond_signal(&pcond);
		printf("%i\n", queue_dequeue());
		iteration_counter--;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main(void)
{
	queue_init();
	pthread_mutex_init(&mutex, NULL);
	
	
	pthread_cond_init(&pcond, NULL);
	pthread_cond_init(&ccond, NULL);
	
	pthread_t thProducer, thConsumer;
	pthread_create(&thProducer, NULL, producer, NULL);
	pthread_create(&thConsumer, NULL, consumer, NULL);
	
	pthread_join(thProducer, NULL);
	pthread_join(thConsumer, NULL);
	
	if (iteration_counter == 0)
		printf("The program completed its work with success.\n");
	else
		printf("The program completed its work without success.\n");
	
	return 0;
}