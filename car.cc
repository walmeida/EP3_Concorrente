#include "car.h"
#include "rollercoastermonitor.h"

#include "passenger.h"

unsigned int Car::next_car_id = 0;

void Car::run () {
    for (int i = 0; i < 50; ++i) {
        rcm_->carrega (this);
        rcm_->descarrega (this);
        deletePassengers ();
    }
}

void Car::removePassenger (Passenger* p) {
    if (p->finishedRide ())
        passenger_delete_list_.push_back (p);
    passenger_list_.remove (p);
}

void Car::deletePassengers () {
    std::list<Passenger*>::iterator it = passenger_delete_list_.begin ();
    for (; it != passenger_delete_list_.end (); ++it) {
        delete *it;
    }
    passenger_delete_list_.clear ();
}
