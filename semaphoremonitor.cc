#include "semaphoremonitor.h"
#include "thread.h"
#include <cstdio>

unsigned long long SemaphoreMonitor::id_ = 0;

SemaphoreMonitor::SemaphoreMonitor () : mutex_(0) {
    sem_name_[0] = '\0';
}

int SemaphoreMonitor::init () {
    sprintf (sem_name_, "sem_monitor%llu", id_);
    mutex_ = sem_open (sem_name_, O_CREAT | O_EXCL, S_IRWXU, 1);
    id_++;
    if (!mutex_ || mutex_ == SEM_FAILED) { // try again
        sem_unlink (sem_name_);
        mutex_ = sem_open (sem_name_, O_CREAT | O_EXCL, S_IRWXU, 1);
    }
    if (!mutex_ || mutex_ == SEM_FAILED)
        return 1;
    return 0;
}

SemaphoreMonitor::~SemaphoreMonitor () {
    sem_close (mutex_);
    sem_unlink (sem_name_);
}

void SemaphoreMonitor::monitorEntry () {
    sem_wait (mutex_);
}

void SemaphoreMonitor::monitorExit () {
    sem_post (mutex_);
}

bool SemaphoreMonitor::empty (ConditionVariable& cv) {
    return cv.empty();
}

void SemaphoreMonitor::wait (ConditionVariable& cv) {
    sem_t* s = Thread::current_thread_sem_;
    cv.insert (s, 0);
    sem_post (mutex_);
    sem_wait (s);
    sem_wait (mutex_);
}

void SemaphoreMonitor::wait (ConditionVariable& cv, unsigned int rank) {
    sem_t* s = Thread::current_thread_sem_;
    cv.insert (s, rank);
    sem_post (mutex_);
    sem_wait (s);
    sem_wait (mutex_);
}

void SemaphoreMonitor::signal (ConditionVariable& cv) {
    if (!cv.empty()) {
        sem_t *s = cv.remove ();
        sem_post (s);
    }
}

void SemaphoreMonitor::signal_all (ConditionVariable& cv) {
    while (!cv.empty()) {
        sem_t *s = cv.remove ();
        sem_post (s);
    }
}

unsigned int minrank (ConditionVariable& cv) {
    return cv.getMinRank ();
}
