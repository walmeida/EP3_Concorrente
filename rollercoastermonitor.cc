#include "rollercoastermonitor.h"
#include "car.h"
#include "passenger.h"
#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;

RollerCoasterMonitor::RollerCoasterMonitor (unsigned int number_of_cars) :
    number_of_cars_(number_of_cars), car_list_(number_of_cars),
    car_moving_(number_of_cars, false), finished_ride_(number_of_cars_, false),
    car_(0), seat_(0), car_loading_(0), car_available_(2),
    open_(number_of_cars), passenger_left_(number_of_cars) {
    if (sm_.init ())
        throw std::runtime_error ("RollerCoasterMonitor: Falha ao inicializar semáforo");
}

RollerCoasterMonitor::~RollerCoasterMonitor () {
    // delete passengers from passenger_queue_ ??
}

void RollerCoasterMonitor::setCar (unsigned int Id, Car* c) {
    car_list_[Id] = c;
}

void RollerCoasterMonitor::pegaCarona (Passenger* p) {
    sm_.monitorEntry ();
    passengers_queue_.push_back (p);
    cout << "Passageiro chegou" << endl << endl;
    printInfo ();
    const unsigned int rank = p->hasGoldenTicket () ? 0 : 1;
    // Se houver alguem na fila, ele precisa entrar nela primeiro
    if (!car_available_.empty()) {
        p->setCurrentThreadSem ();
        sm_.wait (car_available_, rank);
    }
    // Espera para poder entrar no carrinho
    while (car_ == 0) {
        p->setCurrentThreadSem ();
        sm_.wait (car_available_, rank);
    }
    car_--; car_list_[car_loading_]->addPassenger (p);
    passengers_queue_.remove (p);
    const unsigned int myCar = car_loading_;
    seat_--; sm_.signal_all (seat_occupied_);
    // Espera terminar o passeio
    while (!finished_ride_[myCar]) {
        p->setCurrentThreadSem ();
        sm_.wait (open_[myCar]);
    }
    car_list_[myCar]->removePassenger (p);
    sm_.signal (passenger_left_[myCar]);
    sm_.monitorExit ();
}
    
void RollerCoasterMonitor::carrega (Car* c) {
    sm_.monitorEntry ();
    const unsigned int myId = c->getId ();
    while (car_loading_ != myId) {
        c->setCurrentThreadSem ();
        sm_.wait (car_has_loaded_);
    }
    seat_ = c->getCapacity ();
    while (seat_ > 0) {
        car_ = 1;
        sm_.signal (car_available_);
        c->setCurrentThreadSem ();
        sm_.wait (seat_occupied_);
    }
    car_moving_[myId] = true;
    car_loading_ = (car_loading_ + 1) % number_of_cars_;
    sm_.signal_all (car_has_loaded_);
    cout << "Carro " << myId << " saindo" << endl << endl;
    printInfo ();
    sm_.monitorExit ();
}

void RollerCoasterMonitor::descarrega (Car* c) {
    sm_.monitorEntry ();
    const unsigned int myId = c->getId ();
    finished_ride_[myId] = true;
    car_moving_[myId] = false;
    while (!c->empty ()) {
        sm_.signal (open_[myId]);
        c->setCurrentThreadSem ();
        sm_.wait (passenger_left_[myId]);
    }
    finished_ride_[myId] = false;
    cout << "Carro " << myId << " terminou passeio" << endl << endl;
    printInfo ();
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
        if (car_list_[c] == NULL)
            cout << "ERROR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        else
            cout << car_list_[c]->occupiedSeats () << " passageiros: \n\t";
        Car::const_iterator it = car_list_[c]->begin ();
        if (it != car_list_[c]->end ()) {
            (*it)->print ();
            while (++it != car_list_[c]->end ()) {
                cout << ", ";
                (*it)->print ();
            }
        }
        cout << endl;
    }
    cout << "=============================================" << endl;
}
