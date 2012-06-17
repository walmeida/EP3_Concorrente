#include "semaphoremonitor.h"

unsigned long long SemaphoreMonitor::id_ = 0;

SemaphoreMonitor::SemaphoreMonitor () {
    sprintf (sem_name_, "sem_monitor%llu", id_);
    mutex_ = sem_open (sem_name_, O_CREAT | O_EXCL, S_IRWXU, 1);
    id_++;
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

bool SemaphoreMonitor::empty (ConditionVariable<sem_t*>& cv) {
    return cv.empty();
}

void SemaphoreMonitor::wait (Thread& t, ConditionVariable<sem_t*>& cv) {
    sem_t *s = t.getSemaphore ();
    cv.insert (s, 0);
    sem_post (mutex_);
    sem_wait (s);
    sem_wait (mutex_);
}

void SemaphoreMonitor::wait (Thread& t, ConditionVariable<sem_t*>& cv,
                             unsigned int rank) {
    sem_t *s = t.getSemaphore ();
    cv.insert (s, rank);
    sem_post (mutex_);
    sem_wait (s);
    sem_wait (mutex_);
}

void SemaphoreMonitor::signal (ConditionVariable<sem_t*>& cv) {
    if (!cv.empty()) {
        sem_t *s = cv.remove ();
        sem_post (s);
    }
}

void SemaphoreMonitor::signal_all (ConditionVariable<sem_t*>& cv) {
    while (!cv.empty()) {
        sem_t *s = cv.remove ();
        sem_post (s);
    }
}

unsigned int minrank (ConditionVariable<sem_t*>& cv) {
    return cv.getMinRank ();
}
