#include "timemanager.h"
#include <stdexcept>

TimeManager::TimeManager () : time_(0) {
    if (sm_.init ()) {
        throw std::runtime_error ("TimeManager: Falha ao inicializar semáforo");
    }
}

TimeManager::~TimeManager () {}

void TimeManager::advanceTime () {
    sm_.monitorEntry ();
    if (!sleeping_threads_.empty ()) {
        unsigned int new_time = sleeping_threads_.getMinRank ();
        do {
            sm_.signal (sleeping_threads_);
        } while (!sleeping_threads_.empty () && (new_time == sleeping_threads_.getMinRank ()));
    }
    sm_.monitorExit ();
}

unsigned int TimeManager::time () const {
    return time_;
}

void TimeManager::delay (Thread* t, unsigned int interval) {
    sm_.monitorEntry ();
    sm_.wait (sleeping_threads_, time_ + interval);
    sm_.monitorExit ();
}

