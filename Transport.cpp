#include "Transport.h"

bool Transport::operator<(const Transport &other) const {
    return this->dur < other.dur;
}

Transport &Transport::operator=(const Transport &other) {
    if (this == &other) return *this;
    dur = other.dur;
    return *this;
}

Transport &Transport::operator=(Transport &&other) noexcept {
    if (this == &other) return *this;
    dur = other.dur;
    return *this;
}
