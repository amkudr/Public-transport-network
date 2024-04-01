#ifndef HW2_RAIL_H
#define HW2_RAIL_H
#include "Transport.h"

class Rail: public Transport {
public:
    static int stopTime;
public:
    explicit Rail(int dur) : Transport(dur) {}
    int getType() const override;
    int getStopTime() const override;

    static void setStopTime(int time);

    string getName() const override;
};


#endif //HW2_RAIL_H
