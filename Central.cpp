#include "Central.h"
int Central::changeTime = 5;
int Central::getChangeTime() {
    return changeTime;
}

void Central::setChangeTime(int time) {
    changeTime = time;
}
