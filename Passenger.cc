#include "passenger.h"
#include "rollercoastermonitor.h"

void Passenger::run () {
    while (rides_left_) {
        rcm_->pegaCarona (this);
        rides_left_--;
    }
}
