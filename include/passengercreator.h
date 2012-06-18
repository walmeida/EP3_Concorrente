#ifndef PASSENGERCREATOR_H_
#define PASSENGERCREATOR_H_
#include "passenger.h"

class RollerCoasterMonitor;

class PassengerCreator : public Thread {
    public:
        PassengerCreator (RollerCoasterMonitor *rcm);
        ~PassengerCreator ();
        void run ();
    private:
        RollerCoasterMonitor *rcm_;
        bool createGoldenTicket ();
};

#endif // PASSENGERCREATOR_H_
