#include "thread.h"

void* thread_run_wrapper (void * thread) {
    Thread * t = (Thread *) thread;
    t->run ();
    return NULL;
}

unsigned long long Thread::id_ = 0;
