#ifndef SEMAPHORE_MONITOR_H_
#define SEMAPHORE_MONITOR_H_

#include <semaphore.h>
#include "conditionvariable.h"

class SemaphoreMonitor {
    public:
        SemaphoreMonitor ();
        ~SemaphoreMonitor ();
        void monitorEntry ();
        void monitorExit ();
        bool empty (ConditionVariable<sem_t*>& cv);
        void wait (Thread& t, ConditionVariable<sem_t*>& cv);
        void wait (Thread& t, ConditionVariable<sem_t*>& cv,
                   unsigned int rank);
        void signal (ConditionVariable<sem_t*>& cv);
        void signal_all (ConditionVariable<sem_t*>& cv);
        unsigned int minrank (ConditionVariable<sem_t*>& cv);
    private:
        char sem_name_[100];
        static unsigned long long id_;
        sem_t *mutex_;
};

#endif
