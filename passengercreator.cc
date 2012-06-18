#include "passengercreator.h"
#include "rollercoastermonitor.h"
#include <iostream>

PassengerCreator::PassengerCreator (RollerCoasterMonitor *rcm) : rcm_(rcm) {}

PassengerCreator::~PassengerCreator () {}

void PassengerCreator::run () {
    for (int i = 0; i < 20; ++i) {
        Passenger* p = new Passenger (createGoldenTicket (), rcm_);
        int result = p->start ();
        if (result) {
            std::cout << "ERRO " << result << " CRIANDO PASSAGEIRO" << std::endl;
            delete p;
        }

        // TODO TimeManager
        /*
        struct timespec tim, tim2;
        tim.tv_sec = 0;
        tim.tv_nsec = 300;
        nanosleep(&tim , &tim2);
        */
    }
}

bool PassengerCreator::createGoldenTicket () {
    float valor;
    valor = rand() / ( RAND_MAX + 1.0 );
    if(valor > 0.3) 
        return true;
    return false;
}
