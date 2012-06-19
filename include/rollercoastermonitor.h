#ifndef ROLLER_COASTER_MONITOR_H_
#define ROLLER_COASTER_MONITOR_H_

#include <vector>
#include <list>
#include <semaphore.h>
#include "rankconditionvariable.h"
#include "semaphoremonitor.h"

class Car;
class Passenger;

class RollerCoasterMonitor {
    public:
        RollerCoasterMonitor (unsigned int number_of_cars);
        ~RollerCoasterMonitor ();
        void setCar (unsigned int Id, Car* c);
        void pegaCarona (Passenger* p);
        void carrega (Car* c);
        void descarrega (Car* c);
    private:
        void printInfo ();
        SemaphoreMonitor sm_;
        unsigned int number_of_cars_;
        std::vector<Car*> car_list_;
        std::list<Passenger*> passengers_queue_;
        std::vector<bool> car_moving_;
        std::vector<bool> finished_ride_;
        unsigned int car_, seat_, car_loading_;
        RankConditionVariable car_has_loaded_;
        RankConditionVariable car_available_;
        RankConditionVariable seat_occupied_;
        std::vector<RankConditionVariable> open_;
        std::vector<RankConditionVariable> passenger_left_;
};

#endif
