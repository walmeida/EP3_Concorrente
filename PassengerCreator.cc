#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "Passenger.h"

/* Define se o Passageiro terá um bilhete dourado. */
bool PassengerCreator::hasGoldenTicket(){
   float valor;
   valor = rand() / ( RAND_MAX + 1.0 );
   
   if(valor > PROPORCAO)
    return true;
   
   return false;
}

Passenger PassengerCreator::run(){
    Passenger *new_passenger = new Passenger ();
}
