#ifndef PASSENGERCREATOR_H_
#define PASSENGERCREATOR_H_
#include "passenger.h"

class PassengerCreator : public Thread {
    private:
       /*const float PROPORCAO;*/
    public:
        PassengerCreator ();
        ~PassengerCreator ();
};

#endif // PASSENGERCREATOR_H_
