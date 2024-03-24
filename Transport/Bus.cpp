#include "Bus.h"

int Bus::stopTime = 2;

int Bus::getStopTime() const {
    return stopTime;
}

void Bus::setStopTime(int time) {
    stopTime = time;
}

string Bus::getName() const {
    return "bus";
}
