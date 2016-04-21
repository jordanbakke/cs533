#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef unsigned char byte;

typedef enum {
    RUNNING, // The thread is currently running.
    READY,   // The thread is not running, but is runnable.
    BLOCKED, // The thread is not running, and not runnable.
    DONE     // The thread has finished. 
} state_t;

typedef struct {
    byte * stack_pointer;
    void (*initial_function)(void*);
    void * initial_argument;
    state_t state;
} thread;

void scheduler_begin();
void thread_fork(void(*)(void*), void*);
void yield();
void scheduler_end();

extern thread * current_thread;

#endif
