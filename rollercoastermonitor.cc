#include "rollercoastermonitor.h"
#include "car.h"
#include "passenger.h"
#include <iostream>

using std::cout;
using std::endl;

RollerCoasterMonitor::RollerCoasterMonitor (unsigned int number_of_cars) :
    number_of_cars_(number_of_cars), car_list_(number_of_cars),
    car_moving_(number_of_cars, false), finished_ride_(number_of_cars_, false),
    car_(0), seat_(0), car_loading_(0), car_available_(2),
    open_(number_of_cars), passenger_left_(number_of_cars) {};

RollerCoasterMonitor::~RollerCoasterMonitor () {
    // delete passengers from passenger_queue_ ??
}

void RollerCoasterMonitor::setCar (unsigned int Id, Car* c) {
    car_list_[Id] = c;
}

void RollerCoasterMonitor::pegaCarona (Passenger* p) {
    sm_.monitorEntry ();
    printInfo ();
    passengers_queue_.push_back (p);
    sem_t *s = p->getSemaphore ();
    const unsigned int rank = p->hasGoldenTicket () ? 0 : 1;
    while (car_ == 0)
        sm_.wait (s, car_available_, rank);
    car_--; car_list_[car_loading_]->addPassenger (p);
    passengers_queue_.remove (p);
    const unsigned int myCar = car_loading_;
    seat_--; sm_.signal (seat_occupied_);
    while (!finished_ride_[myCar])
        sm_.wait (s, open_[myCar]);
    car_list_[car_loading_]->removePassenger (p);
    sm_.signal (passenger_left_[myCar]);
    sm_.monitorExit ();
}
    
void RollerCoasterMonitor::carrega (Car* c) {
    sm_.monitorEntry ();
    printInfo ();
    sem_t *s = c->getSemaphore ();
    while (car_loading_ != c->getId ())
        sm_.wait (s, car_has_loaded_);
    seat_ = c->getCapacity ();
    while (seat_ != 0) {
        car_ = 1;
        sm_.signal (car_available_);
        sm_.wait (s, seat_occupied_);
    }
    car_loading_ = (car_loading_ + 1) % number_of_cars_;
    sm_.signal_all (car_has_loaded_);
    sm_.monitorExit ();
}

void RollerCoasterMonitor::descarrega (Car* c) {
    sm_.monitorEntry ();
    printInfo ();
    sem_t *s = c->getSemaphore ();
    const unsigned int myId = c->getId ();
    finished_ride_[myId] = true;
    while (!c->empty ()) {
        sm_.signal (open_[myId]);
        sm_.wait (s, passenger_left_[myId]);
    }
    finished_ride_[myId] = false;
    sm_.monitorExit ();
}

void RollerCoasterMonitor::printInfo () {
    // Imprimindo passageiros na fila
    {
        cout << passengers_queue_.size () << " passageiros na fila: \n\t";
        std::list<Passenger*>::const_iterator it = passengers_queue_.begin ();
        if (it != passengers_queue_.end ()) {
            (*it)->print ();
            while (++it != passengers_queue_.end ()) {
                cout << ", ";
                (*it)->print ();
            }
        }
        cout << endl;
    }
    // Imprimindo passageiros nos carros
    for (unsigned int c = 0; c < number_of_cars_; ++c) {
        cout << "Carro " << c << " - ";
        if (car_moving_[c])
            cout << "Movendo-se com ";
        else
            cout << "Parado com ";
        cout << car_list_[c]->occupiedSeats () << " passageiros: \n\t";
        Car::const_iterator it = car_list_[c]->begin ();
        if (it != car_list_[c]->end ()) {
            (*it)->print ();
            while (++it != car_list_[c]->end ()) {
                cout << ", ";
                (*it)->print ();
            }
        }
    }
    cout << endl;
    cout << "=============================================" << endl;
}
