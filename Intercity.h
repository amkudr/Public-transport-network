
#ifndef HW2_INTERCITY_H
#define HW2_INTERCITY_H


#include <utility>

#include "Station.h"

class Intercity : public Station {
private:
    static int changeTime;
public:
    explicit Intercity(string name) : Station(std::move(name)) {};

    int getChangeTime() override;

    static void setChangeTime(int time);


};


#endif //HW2_INTERCITY_H
