#ifndef SEMAPHORE_MONITOR_H_
#define SEMAPHORE_MONITOR_H_

#include <semaphore.h>
#include "conditionvariable.h"

class SemaphoreMonitor {
    public:
        SemaphoreMonitor ();
        ~SemaphoreMonitor ();
        int init ();
        void monitorEntry ();
        void monitorExit ();
        bool empty (ConditionVariable& cv);
        void wait (ConditionVariable& cv);
        void wait (ConditionVariable& cv, unsigned int rank);
        void signal (ConditionVariable& cv);
        void signal_all (ConditionVariable& cv);
        unsigned int minrank (ConditionVariable& cv);
    private:
        char sem_name_[100];
        static unsigned long long id_;
        sem_t *mutex_;
};

#endif
