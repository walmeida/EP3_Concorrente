#ifndef PASSENGER_H_
#define PASSENGER_H_

#include "Thread.h"

class Passenger : public Thread {
    private:
        bool goldenTicket;
    public:
        Passenger (bool hasTicket);
        ~Passenger ();
};

#endif // PASSENGER_H_
