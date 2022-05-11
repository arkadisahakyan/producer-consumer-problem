/*
 * Created by Arkady Sahakyan.
 */

#include <stdlib.h>
#include <stdbool.h>

void queue_init();
void queue_enqueue(int value);
int queue_dequeue();
bool queue_is_full();
bool queue_is_empty();
int queue_size();