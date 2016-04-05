typedef unsigned char byte;

typedef struct {
    byte * stack_pointer;
    void (*initial_function)(void*);
    void * initial_argument;
} thread;

void thread_switch(thread*, thread*);
void thread_start(thread*, thread*);
void thread_wrap();
