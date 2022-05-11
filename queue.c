/*
 * Created by Arkady Sahakyan.
 */

#include "queue.h"

#define CAPACITY 8

static int* queue;
static int head;
static int tail;

void queue_init()
{
	queue = malloc(CAPACITY * sizeof(int));
	head = -1;
	tail = 0;
}

void queue_enqueue(int value)
{
	if (queue_is_full())
		exit(1);
	queue[tail] = value;
	if (head == -1)
		head = 0;
	if (tail == CAPACITY - 1)
		tail = 0;
	else
		tail++;
}

int queue_dequeue()
{
	if (queue_is_empty())
		exit(1);
	int item = queue[head];
	if (head != CAPACITY - 1)
		head++;
	else
		head = 0;
	if (head == tail)
	{
		head = -1;
		tail = 0;
	}
	return item;
}

bool queue_is_full()
{
	return head == tail;
}

bool queue_is_empty()
{
	return head == -1;
}

int queue_size()
{
	if (head != -1)
	{
		return head < tail ? tail - head : (CAPACITY - head) + tail;
	}
	return 0;
}