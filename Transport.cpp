#include "Transport.h"

bool Transport::operator<(const Transport &other) const {
    return this->dur < other.dur;
}
int Transport::stopTime = 3;
