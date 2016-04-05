#include <stdio.h>
#include <stdlib.h>

#include "mythreads.h"

#define STACK_SIZE 0x100000 // megabyte

thread * current_thread;
thread * inactive_thread;

void thread_wrap()
{
    current_thread->initial_function(current_thread->initial_argument);
}

void yield()
{
    thread * temp = current_thread;
    current_thread = inactive_thread;
    inactive_thread = temp;
    thread_switch(inactive_thread, current_thread);
}

void do_something(void * arg)
{
    printf("%d\n", *((int*) arg));
    yield();
}

int main(int argc, char *argv[])
{
    current_thread = malloc(sizeof(thread));
    
    current_thread->initial_function = do_something;
    
    current_thread->initial_argument = malloc(sizeof(int));
    *((int*) current_thread->initial_argument) = 42;
    
    current_thread->stack_pointer = malloc(STACK_SIZE) + STACK_SIZE;
    
    inactive_thread = malloc(sizeof(thread));
    
    thread_start(inactive_thread, current_thread);
    
    return 0;
}
