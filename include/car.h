#ifndef CAR_H_
#define CAR_H_

#include <list>
#include "thread.h"
#include "passenger.h"

class RollerCoasterMonitor;

class Car : public Thread {
    public:
        Car (RollerCoasterMonitor *rcm, unsigned int capacity) : 
            rcm_(rcm), capacity_(capacity), isRunning_(false), 
            passenger_list_() {
            car_id_ = next_car_id++;
        }
        ~Car () {}
        void run ();
        void addPassenger (Passenger* p) {
            passenger_list_.push_back (p);
        }
        void removePassenger (Passenger* p) {
            passenger_list_.remove (p);
        }
        unsigned int getId () const {
            return car_id_;
        }
        unsigned int getCapacity () const {
            return capacity_;
        }
        bool empty () const {
            return passenger_list_.empty ();
        }
    private:
        RollerCoasterMonitor *rcm_;
        static unsigned int next_car_id;
        unsigned int car_id_;
        unsigned int capacity_;
        bool isRunning_;
        std::list<Passenger*> passenger_list_;
};
        
#endif
