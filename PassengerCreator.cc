#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "passengerCreator.h"

/* Define se o Passageiro terá um bilhete dourado. */
bool hasGoldenTicket(){
   float valor;
   valor = rand() / ( RAND_MAX + 1.0 );
   
   if(valor > 0.3)
    return true;
   
   return false;
}

/*Passenger run(){
   Passenger *new_passenger = new Passenger ();
   return *new_passenger;
}*/
