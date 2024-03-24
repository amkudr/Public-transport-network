
#ifndef HW2_CENTRAL_H
#define HW2_CENTRAL_H
#include "Station.h"


class Central: public Station {
private:
    static int changeTime;
public:

    explicit Central(string name) : Station(std::move(name)) {};

    int getChangeTime() override;

    static void setChangeTime(int time);

};


#endif //HW2_CENTRAL_H
