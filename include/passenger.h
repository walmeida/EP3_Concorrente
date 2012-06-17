#ifndef PASSENGER_H_
#define PASSENGER_H_

#include <cstdlib>
#include "thread.h"

class RollerCoasterMonitor;

class Passenger : public Thread {
    public:
        Passenger (RollerCoasterMonitor *rcm) : rcm_(rcm), rides_left_(2) {
            goldenTicket = createGoldenTicket();
        }
        ~Passenger () {}
        void run ();
        bool hasGoldenTicket () const {
            return goldenTicket;
        }
    private:
        RollerCoasterMonitor *rcm_;
        unsigned int rides_left_;
        bool goldenTicket;
        bool createGoldenTicket(){
            float valor;
            valor = rand() / ( RAND_MAX + 1.0 );
            if(valor > 0.3) 
                return true;
            return false;
        }
};

#endif // PASSENGER_H_
