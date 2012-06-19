#ifndef CONDITION_VARIABLE_H_
#define CONDITION_VARIABLE_H_

#include <semaphore.h>

class ConditionVariable {
    public:
        virtual ~ConditionVariable () {}
        virtual void insert (sem_t* s, unsigned int rank) = 0;
        virtual sem_t* remove () = 0;
        virtual bool empty () const = 0;
        virtual unsigned int getMinRank () const = 0;
};

#endif
