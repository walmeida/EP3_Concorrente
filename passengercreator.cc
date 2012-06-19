#include "passengercreator.h"
#include "rollercoastermonitor.h"
#include "timemanager.h"
#include <iostream>

PassengerCreator::PassengerCreator (RollerCoasterMonitor *rcm, TimeManager* tm) :
        rcm_(rcm), tm_(tm) {
            delay_ = (unsigned int) (1.0 / taxa);
}

PassengerCreator::~PassengerCreator () {}

void PassengerCreator::run () {
    for (int i = 0; i < 20; ++i) {
        Passenger* p = new Passenger (createGoldenTicket (), rcm_);
        int result = p->start ();
        if (result) {
            std::cout << "ERRO " << result << " CRIANDO PASSAGEIRO" << std::endl;
            delete p;
        }
        
        tm_->delay (this, delay_);
    }
}

bool PassengerCreator::createGoldenTicket () {
    float valor;
    valor = rand() / ( RAND_MAX + 1.0 );
    if(valor > 0.3) 
        return true;
    return false;
}
