#ifndef ROLLER_COASTER_MONITOR_H_
#define ROLLER_COASTER_MONITOR_H_

#include <vector>
#include <semaphore.h>
#include "conditionvariable.h"
#include "semaphoremonitor.h"
#include "car.h"
#include "passenger.h"

class RollerCoasterMonitor {
    public:
        RollerCoasterMonitor (unsigned int number_of_cars);
        ~RollerCoasterMonitor ();
        void pegaCarona (Passenger& p);
        void carrega (Car& c);
        void descarrega (Car& c);
    private:
        SemaphoreMonitor sm_;
        unsigned int number_of_cars_;
        std::vector<Car*> car_list_;
        std::list<Passenger*> passengers_queue_;
        std::vector<bool> car_moving_;
        std::vector<bool> finished_ride_;
        unsigned int car_, seat_, car_loading_;
        ConditionVariable<sem_t*> car_has_loaded_;
        ConditionVariable<sem_t*> car_available_;
        ConditionVariable<sem_t*> seat_occupied_;
        std::vector<ConditionVariable<sem_t*> > open_;
        std::vector<ConditionVariable<sem_t*> > passenger_left_;
};

#endif
