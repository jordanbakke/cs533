#include <stdlib.h>
#include <stdio.h> // for debugging

#include "scheduler.h"
#include "queue.h"

#define STACK_SIZE 0x100000 // megabyte

extern void thread_switch(thread*, thread*);
extern void thread_start(thread*, thread*);

thread * current_thread;
queue ready_list;

void thread_wrap()
{
    current_thread->initial_function(current_thread->initial_argument);
    current_thread->state = DONE;
    yield();
}

void scheduler_begin()
{
    current_thread = malloc(sizeof(thread));
    current_thread->state = RUNNING;
    
    ready_list.head = NULL;
    ready_list.tail = NULL;
}

void thread_fork(void(*target)(void*), void * arg)
{
    thread * old;
    thread * new;
    
    old = current_thread;
    old->state = READY;
    thread_enqueue(&ready_list, old);
    
    new = malloc(sizeof(thread));
    new->stack_pointer = malloc(STACK_SIZE) + STACK_SIZE;
    new->initial_function = target;
    new->initial_argument = arg;
    new->state = RUNNING;
    
    current_thread = new;
    thread_start(old, new);
}

void yield()
{
    thread * old;
    thread * new;
    
    old = current_thread;
    if (old->state != DONE)
    {
        old->state = READY;
        thread_enqueue(&ready_list, old);
    }
    new = thread_dequeue(&ready_list);
    new->state = RUNNING;
    current_thread = new;
    
    thread_switch(old, new);
}

void scheduler_end()
{
    while(is_empty(&ready_list) == 0)
    {
        yield();
    }
}
