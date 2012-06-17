#ifndef CAR_H_
#define CAR_H_

#include <list>
#include "thread.h"
#include "passenger.h"

class RollerCoasterMonitor;

class Car : public Thread {
    public:
        Car (RollerCoasterMonitor *rcm, unsigned int capacity) : 
            rcm_(rcm), capacity_(capacity), passenger_list_() {
            carId_ = nextCarId++;
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
            return carId_;
        }
        unsigned int getCapacity () const {
            return capacity_;
        }
        bool empty () const {
            return passenger_list_.empty ();
        }
    private:
        RollerCoasterMonitor *rcm_;
        static unsigned int nextCarId;
        unsigned int carId_;
        unsigned int capacity_;
        std::list<Passenger*> passenger_list_;
};
        
#endif
