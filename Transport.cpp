//
// Created by Anton on 03/03/2024.
//

#include "Transport.h"

bool Transport::operator<(const Transport &other) const {
    return this->StopTime < other.StopTime;
}
