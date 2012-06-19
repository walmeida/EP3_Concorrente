#include "car.h"
#include "rollercoastermonitor.h"
#include "timemanager.h"

#include "passenger.h"

unsigned int Car::next_car_id = 0;

void Car::run () {
    while (1) {
        rcm_->carrega (this);
        tm_->delay (this, 100);
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
