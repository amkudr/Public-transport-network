#include "Tram.h"

int Tram::stopTime = 3;

int Tram::getType() const {
    return 1;
}

int Tram::getStopTime() const {
    return stopTime;
}

void Tram::setStopTime(int time) {
    stopTime = time;
}

string Tram::getName() const {
    return "tram";
}
