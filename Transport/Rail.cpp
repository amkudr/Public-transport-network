#include "Rail.h"

int Rail::stopTime = 5;

int Rail::getType() const {
    return 3;
}

int Rail::getStopTime() const {
    return stopTime;
}

void Rail::setStopTime(int time) {
    stopTime = time;
}

string Rail::getName() const {
    return "rail";
}
