#include "passenger.h"
#include "rollercoastermonitor.h"

unsigned int Passenger::next_passenger_id_ = 0;

void Passenger::run () {
    while (rides_left_) {
        rides_left_--;
        rcm_->pegaCarona (this);
    }
}
