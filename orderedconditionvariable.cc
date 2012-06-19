#include "orderedconditionvariable.h"

OrderedConditionVariable::OrderedConditionVariable () :
    queue_() {}

OrderedConditionVariable::~OrderedConditionVariable () {
    std::set<WaitingThread*, WaitingThreadComp>::iterator it;
    it = queue_.begin ();
    for (; it != queue_.end (); ++it) {
        delete *it;
    }
}

void OrderedConditionVariable::insert (sem_t* s, unsigned int rank) {
    WaitingThread* wt = new WaitingThread();
    wt->s = s;
    wt->deadline = rank;
    queue_.insert(wt);
}

sem_t* OrderedConditionVariable::remove () {
    std::set<WaitingThread*, WaitingThreadComp>::iterator it;
    it = queue_.begin ();
    WaitingThread* wt = *it;
    queue_.erase (it);
    sem_t* s = wt->s;
    delete wt;
    return s;
}

bool OrderedConditionVariable::empty () const {
    return queue_.empty ();
}

unsigned int OrderedConditionVariable::getMinRank () const {
    std::set<WaitingThread*, WaitingThreadComp>::const_iterator it;
    it = queue_.begin ();
    const WaitingThread* wt = *it;
    return wt->deadline;
}
