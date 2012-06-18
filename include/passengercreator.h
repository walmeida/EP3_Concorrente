#ifndef PASSENGERCREATOR_H_
#define PASSENGERCREATOR_H_
#include "passenger.h"

class PassengerCreator : public Thread {
    private:
    public:
        PassengerCreator ();
        ~PassengerCreator ();
        void creator(RollerCoasterMonitor *rcm);
};

#endif // PASSENGERCREATOR_H_
