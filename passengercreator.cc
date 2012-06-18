#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "passengercreator.h"

PassengerCreator::PassengerCreator () {
    
}

PassengerCreator::~PassengerCreator () {

}

void PassengerCreator::creator (RollerCoasterMonitor *rcm) {
   Passenger p(rcm);
   p.start ();
}
