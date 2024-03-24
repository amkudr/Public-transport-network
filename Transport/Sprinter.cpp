#include "Sprinter.h"

int Sprinter::stopTime = 4;

int Sprinter::getType() const {
    return 2;
}

int Sprinter::getStopTime() const {
    return stopTime;
}

void Sprinter::setStopTime(int time) {
    stopTime = time;
}

string Sprinter::getName() const {
    return "sprinter";
}
