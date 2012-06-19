#ifndef ORDERED_CONDITION_VARIABLE_H_
#define ORDERED_CONDITION_VARIABLE_H_

#include "conditionvariable.h"
#include <set>

class OrderedConditionVariable : public ConditionVariable {
    public:
        OrderedConditionVariable ();
        ~OrderedConditionVariable ();
        void insert (sem_t* s, unsigned int rank);
        sem_t* remove ();
        bool empty () const;
        unsigned int getMinRank () const;
    private:
        class WaitingThread {
            public:
                WaitingThread () {}
                ~WaitingThread () {};
                sem_t* s;
                unsigned int deadline;
        };
        struct WaitingThreadComp {
            bool operator() (WaitingThread* const& lhs, WaitingThread* const& rhs) const {
                if (lhs->deadline == rhs->deadline)
                    return lhs->s < rhs->s;
                return lhs->deadline < rhs->deadline;
            }
        };
        std::set<WaitingThread*, WaitingThreadComp> queue_;
};

#endif
