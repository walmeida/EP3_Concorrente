#ifndef PASSENGERCREATOR_H_
#define PASSENGERCREATOR_H_
#include "passenger.h"

class RollerCoasterMonitor;
class TimeManager;
extern float taxa;

class PassengerCreator : public Thread {
    public:
        PassengerCreator (RollerCoasterMonitor *rcm, TimeManager* tm);
        ~PassengerCreator ();
        void run ();
    private:
        RollerCoasterMonitor* rcm_;
        TimeManager* tm_;
        unsigned int delay_;
        bool createGoldenTicket ();
};

#endif // PASSENGERCREATOR_H_
