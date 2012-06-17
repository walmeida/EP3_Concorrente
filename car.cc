#include "car.h"
#include "rollercoastermonitor.h"

unsigned int Car::next_car_id = 0;

void Car::run () {
    while(1) {
        rcm_->carrega (this);
        rcm_->descarrega (this);
    }
}

