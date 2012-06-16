#ifndef CAR_H_
#define CAR_H_

#include "thread.h"

class Car : public Thread {
    public:
        Car () {}
        ~Car () {}
        void run () {
            for (int i = 0; i < 5; ++i)
                std::cout << "Car is running" << std::endl;
        }
};
        
#endif
