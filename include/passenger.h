#ifndef PASSENGER_H_
#define PASSENGER_H_

#include <cstdlib>
#include "thread.h"

class RollerCoasterMonitor;

class Passenger : public Thread {
    public:
        Passenger (bool goldenTicket, RollerCoasterMonitor *rcm) : 
                rcm_(rcm), rides_left_(2), goldenTicket_(goldenTicket) {
            passenger_id_ = next_passenger_id_++;
            if (goldenTicket_) {
                sprintf (print_id_, "D%u:", passenger_id_);
            } else {
                sprintf (print_id_, "%u:", passenger_id_);
            }
        }
        ~Passenger () {}
        void run ();
        void print () const {
            std::cout << print_id_ << (2 - rides_left_ - 1);
        }
        bool hasGoldenTicket () const {
            return goldenTicket_;
        }
        bool finishedRide () const {
            return rides_left_ == 0;
        }
    private:
        static unsigned int next_passenger_id_;
        unsigned int passenger_id_;
        char print_id_[100];
        RollerCoasterMonitor *rcm_;
        unsigned int rides_left_;
        bool goldenTicket_;
};

#endif // PASSENGER_H_
