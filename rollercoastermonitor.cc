#include "rollercoastermonitor.h"

RollerCoasterMonitor::RollerCoasterMonitor (unsigned int number_of_cars) :
    number_of_cars_(number_of_cars), car_list_(number_of_cars),
    car_moving_(number_of_cars, false),
    car_(0), seat_(0), car_loading_(0), car_available_(2) {};

RollerCoasterMonitor::~RollerCoasterMonitor () {
    // delete passengers from passenger_queue_ ??
}

void RollerCoasterMonitor::pegaCarona (Passenger& p) {
    sm_.monitorEntry ();
    passengers_queue_.push_back (&p);
    sem_t *s = p.getSemaphore ();
    const unsigned int rank = p.hasGoldenTicket () ? 0 : 1;
    while (car_ == 0)
        sm_.wait (s, car_available_, rank);
    car_--; car_list_[car_loading_]->addPassenger (&p);
    const unsigned int myCar = car_loading_;
    seat_--; sm_.signal (seat_occupied_);
    while (!finished_ride_[myCar])
        sm_.wait (s, open_[myCar]);
    car_list_[car_loading_]->removePassenger (&p);
    sm_.signal (passenger_left_[myCar]);
    sm_.monitorExit ();
}
    
void RollerCoasterMonitor::carrega (Car& c) {
    sm_.monitorEntry ();
    sem_t *s = c.getSemaphore ();
    while (car_loading_ != c.getId ())
        sm_.wait (s, car_has_loaded_);
    seat_ = c.getCapacity ();
    while (seat_ != 0) {
        car_ = 1;
        sm_.signal (car_available_);
        sm_.wait (s, seat_occupied_);
    }
    car_loading_ = (car_loading_ + 1) % number_of_cars_;
    sm_.signal_all (car_has_loaded_);
    sm_.monitorExit ();
}

void RollerCoasterMonitor::descarrega (Car& c) {
    sm_.monitorEntry ();
    sem_t *s = c.getSemaphore ();
    const unsigned int myId = c.getId ();
    finished_ride_[myId] = true;
    while (!c.empty ()) {
        sm_.signal (open_[myId]);
        sm_.wait (s, passenger_left_[myId]);
    }
    finished_ride_[myId] = false;
    sm_.monitorExit ();
}
