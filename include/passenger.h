#ifndef PASSENGER_H_
#define PASSENGER_H_

#include <cstdlib>
#include "thread.h"

class Passenger : public Thread {
    public:
        Passenger (){
          goldenTicket = hasGoldenTicket();
        };
        ~Passenger (){}
        void run () {
            for (int i = 0; i < 5; ++i)
                std::cout << "Passenger is alive! Has he a golden ticket? - " << std::boolalpha << goldenTicket << std::endl;
        }
        
        bool hasGoldenTicket(){
           float valor;
           valor = rand() / ( RAND_MAX + 1.0 );
           if(valor > 0.3) 
             return true;
           return false;
        }
    private:
      bool goldenTicket;
};

#endif // PASSENGER_H_
