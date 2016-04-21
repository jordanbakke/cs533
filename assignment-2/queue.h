#ifndef QUEUE_H
#define QUEUE_H

/*
 * CS533 Course Project
 * Thread Queue ADT
 * queue.h
 *
 * Feel free to modify this file. Please thoroughly comment on
 * any changes you make.
 */
 
#include "scheduler.h"

typedef struct queue_node {
    thread * t;
    struct queue_node * next;  
} queue_node;

typedef struct {
    queue_node * head;
    queue_node * tail;
} queue;

void thread_enqueue(queue * q, thread * t);
thread * thread_dequeue(queue * q);
int is_empty(queue * q);

#endif
