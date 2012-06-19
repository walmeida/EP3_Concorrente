#ifndef TIME_MANAGER_H_
#define TIME_MANAGER_H_

#include "thread.h"
#include "semaphoremonitor.h"
#include "orderedconditionvariable.h"

class TimeManager : public Thread {
    public:
        TimeManager ();
        ~TimeManager ();
        void advanceTime ();
        unsigned int time () const;
        void delay (Thread* t, unsigned int interval);
    private:
        unsigned int time_;
        SemaphoreMonitor sm_;
        OrderedConditionVariable sleeping_threads_;
};

#endif // TIMEMANAGER_H_
