#ifndef HW2_STAD_H
#define HW2_STAD_H
#include "Station.h"

class Stad: public Station {

private:
    static int changeTime;

public:

    explicit Stad(string name) : Station(std::move(name)) {};

    int getChangeTime() override;

    static void setChangeTime(int time);

};


#endif //HW2_STAD_H
